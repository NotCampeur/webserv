#include "CgiHandler.hpp"
#include "InitiationDispatcher.hpp"
#include "Utils.hpp"
#include "Mime.hpp"
#include "unistd.h"
#include "SystemException.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

CgiHandler::CgiHandler(Request & req, Response & resp, int pipe_one[2], std::string method) :
_request(req),
_response(resp),
_method(method),
_file_ext(Utils::get_file_ext(resp.get_path())),
_event_flag(POLLOUT),
_pid(0),
_written_size(0),
_cgi_done(false),
_parser(resp)
{
	std::cerr << "Pipe one fds: " << pipe_one[0] << " ; " << pipe_one[1] << '\n';
	_pipe_one_fd[0] = pipe_one[0];
	_pipe_one_fd[1] = pipe_one[1];
	_pipe_two_fd[0] = 0;
	_pipe_two_fd[1] = 0;
	set_environment();
	if (!open_pipe_two())
	{
		manage_error();
	}
	else
	{
		if (!set_nonblock())
		{
			close_pipes();
			manage_error();
		}
	}
	_response.set_handler_fd(_pipe_one_fd[1]);
	start_cgi();
}

CgiHandler::~CgiHandler(void)
{
	if (!_cgi_done)
	{
		if (waitpid(_pid, NULL, WNOHANG) == 0)
		{
			kill(_pid, SIGTERM);
		}
	}
	close_pipes();
}

void 
CgiHandler::readable(void)
{
	/*
	Check if cgi process is terminated and if any error occured there
	Read from pipe (READ_BUF_SIZE)
	Parse buffer using cgi_parser
	Once parsing is done: Set response params
	*/

	if (_response.complete() || _response.ready_to_send())
	{
		return ;
	}

	if (cgi_process_error())
	{
		close_pipes();
		return ;
	}

	char		read_buff[FILE_READ_BUF_SIZE];
	ssize_t		bytes_read;

	bytes_read = read(_pipe_two_fd[0], read_buff, FILE_READ_BUF_SIZE);

	switch (bytes_read)
	{
		case -1 :
		{
			manage_error();
			Logger(LOG_FILE, error_type, error_lvl) << "Read: " << std::strerror(errno);
		}
		case 0 :
		{
			std::cerr << "Cgi Pipe empty - done reading\n";
			make_complete();
		}
		default :
		{
			_parser.parse(read_buff, bytes_read);
			if (bytes_read < FILE_READ_BUF_SIZE)
			{
				std::cerr << "Read less than Buf_Size\n";
				// make_complete(); Might need TBU
			}
		}
	}
	// Logger(LOG_FILE, basic_type, minor_lvl) << "Socket content (" << bytes_read << " byte(s) read): " << std::string(read_buff, bytes_read);
}

void
CgiHandler::writable(void)
{
	if (_response.complete())
	{
		return ;
	}

	if (_method == "POST" && _request.bodysize() > 0)
	{
		//Exposed if max pipe capacity is reached
		ssize_t len = write(_pipe_one_fd[1], &(_request.get_body()[_written_size]), _request.bodysize() - _written_size);
		if (len < 0)
		{
			manage_error();
			Logger(LOG_FILE, error_type, error_lvl) << "Write: " << std::strerror(errno);
		}
		_written_size += len;
		if (static_cast<size_t>(_written_size) < _request.bodysize())
		{
			return ;
		}
	}
	int ret = dup2(_pipe_two_fd[0], _pipe_one_fd[1]); // Replace write fd by read fd so we can keep using this object + closing write fd so that if there's an error in child, main process will get a "read event"
	if (ret < 0)
	{
		manage_error();
		Logger(LOG_FILE, error_type, error_lvl) << "dup2: " << std::strerror(errno);
	}
	else
	{
		close(_pipe_two_fd[0]);
		_pipe_two_fd[0] = _pipe_one_fd[1];
		_pipe_one_fd[1] = 0;
		_event_flag = POLLIN;
	}
}

bool
CgiHandler::is_timeoutable(void) const
{
	return false;
}

bool
CgiHandler::is_timeout(void) const
{
	return false;
}

int
CgiHandler::get_event_flag(void) const
{
	return _event_flag;
}

void
CgiHandler::set_environment(void)
{
	if (!_request.get_body().empty())
	{
	// Content Lenght
		{
			std::stringstream ss;
			ss << _request.get_body().size();
			_env.add_cgi_env_var("CONTENT_LENGTH", ss.str());
		}
	// Content Type
		{
			const std::string *mime_ext = Mime::get_content_type(_file_ext);
			if (mime_ext != NULL)
			{
				_env.add_cgi_env_var("CONTENT_TYPE", *mime_ext);
			}
		}
	}
	_env.add_cgi_env_var("GATEWAY_INTERFACE", "CGI/1.1");
	_env.add_cgi_env_var("PATH_INFO", _response.get_path()); // /!\ NEEDS TO BE THE FULL PATH!!
	_env.add_cgi_env_var("PATH_TRANSLATED", _response.get_path()); // /!\ This is most likely wrong, but at this point, I am not sure what this variable is about
	_env.add_cgi_env_var("QUERY_STRING", _request.uri().query);
	_env.add_cgi_env_var("REMOTE_ADDR", _response.get_ip());
	_env.add_cgi_env_var("REMOTE_HOST", "NULL"); //Clients are not expected to have a domain name
	_env.add_cgi_env_var("REQUEST_METHOD", _method);
	if (_request.get_config()->cgi().find(_file_ext) != _request.get_config()->cgi().end())
	{
		_env.add_cgi_env_var("SCRIPT_NAME", _request.get_config()->cgi().find(_file_ext)->second);
	}
	else
	{
		_env.add_cgi_env_var("SCRIPT_NAME", "NULL");
	}
	_env.add_cgi_env_var("SERVER_PORT", _request.get_config()->port());
	_env.add_cgi_env_var("SERVER_PROTOCOL", "HTTP/1.1");
	_env.add_cgi_env_var("SERVER_SOFTWARE", "webserv/1.0");

	Request::cookies_t cookies = _request.get_cookies();
	for (size_t i = 0; i < cookies.size(); i++)
	{
		_env.add_http_env_var("COOKIE", cookies[i]);
	}
}

void
CgiHandler::start_cgi(void)
{
	/*
	start new process
	Set new process stdin/stdout to pipe in/out
	execve with cgi env
	*/

	_pid = fork();
	if (_pid < 0)
	{
		manage_error();
		Logger(LOG_FILE, error_type, error_lvl) << "Fork: " << std::strerror(errno);
	}
	if (_pid == 0)
	{
		// std::cerr << "Hello from chile\n";
		close(_pipe_one_fd[1]);
		close(_pipe_two_fd[0]);
		int ret = dup2(_pipe_one_fd[0], STDIN_FILENO);
		if (ret < 0)
		{
			exit(EXIT_FAILURE);
		}
		ret = dup2(_pipe_two_fd[1], STDOUT_FILENO);
		if (ret < 0)
		{
			exit(EXIT_FAILURE);
		}
		const std::string cgi_bin = _request.get_config()->cgi().find(_file_ext)->second;
		if (cgi_bin.empty() == true)
		{
			exit(EXIT_FAILURE);
		}
		else
		{
			char * const av[] = {
				const_cast<char *>(cgi_bin.c_str()),
				const_cast<char *>(_response.get_path().c_str()),
				NULL
				};
			// std::cerr << "Chile about to execve\n";
			execve(cgi_bin.c_str(), av, _env.get_cgi_env()); // /!\ For now, won't generate any cmd line arguments, seems like it should work without it
		}
		Logger(LOG_FILE, error_type, error_lvl) << "Execve: " << std::strerror(errno);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(_pipe_one_fd[0]);
		close(_pipe_two_fd[1]);
		// if (ret < 0)
		// {
		// 	manage_error();
		// 	Logger(LOG_FILE, error_type, error_lvl) << "Pipe: " << std::strerror(errno);
		// }
	}
}

void
CgiHandler::manage_error(void)
{
	if (!_response.metadata_sent())
	{
		_response.http_error(StatusCodes::INTERNAL_SERVER_ERROR_500);
	}
	else
	{
		make_complete();
	}
}

void
CgiHandler::make_complete(void)
{
	_response.ready_to_send() = true;
	_response.complete() = true;
}

bool
CgiHandler::cgi_process_error(void)
{
	if (!_cgi_done)
	{
		int status = 0;
		if (waitpid(_pid, &status, WNOHANG) == _pid)
		{
			_cgi_done = true;
			if (WEXITSTATUS(status) != EXIT_SUCCESS)
			{
				Logger(LOG_FILE, error_type, error_lvl) << "CGI error - exit status:" << WEXITSTATUS(status);
				manage_error();
				return true;
			}
		}
	}
	return false;
}

bool
CgiHandler::open_pipe_two(void)
{
	int ret = pipe(_pipe_two_fd);
	if (ret < 0)
	{
		close_pipes();
		Logger(LOG_FILE, error_type, error_lvl) << "Pipe: " << std::strerror(errno);
		return false;
	}
	return true;
}

bool
CgiHandler::set_nonblock(void)
{
	int ret = fcntl(_pipe_one_fd[1], F_SETFL, O_NONBLOCK);
	if (ret == -1)
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Fcntl: " << std::strerror(errno);
		return false;
	}
	ret = fcntl(_pipe_two_fd[0], F_SETFL, O_NONBLOCK);
	if (ret == -1)
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Fcntl: " << std::strerror(errno);
		return false;
	}
	return true;
}

//Not closing pipe[1] as it is the CgiHandler handle, it will be  closed by ClientHandler call to response.reset()
void
CgiHandler::close_pipes(void)
{
	if (_pipe_one_fd[0] != 0)
	{
		close(_pipe_one_fd[0]);
		_pipe_one_fd[0] = 0;
	}
	// if (_pipe_one_fd[1] != 0)
	// 	close(_pipe_one_fd[1]);
	if (_pipe_two_fd[0] != 0)
	{
		close(_pipe_two_fd[0]);
		_pipe_two_fd[0] = 0;
	}
	if (_pipe_two_fd[1] != 0)
	{
		close(_pipe_two_fd[1]);
		_pipe_two_fd[1] = 0;
	}
}