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
_server_write_pipe(pipe_one[1]),
_server_read_pipe(0),
_cgi_write_pipe(0),
_cgi_read_pipe(pipe_one[0]),
_event_flag(POLLOUT),
_pid(0),
_written_size(0),
_cgi_done(false),
_parser(resp)
{
	std::cerr << "Pipe one fds: " << pipe_one[0] << " ; " << pipe_one[1] << '\n';
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
		}
	}
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
	make_complete(); //Due to the behavior of read and poll on linux, there is no way to know from a read that the pipe is closed if there is content in the pipe. Therefore, when the poll detects an empty closed pipe, it gives a POLLHUP and from this we know that the response is complete
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

	bytes_read = read(_server_read_pipe, read_buff, FILE_READ_BUF_SIZE);

	switch (bytes_read)
	{
		case -1 :
		{
			manage_error();
			Logger(LOG_FILE, error_type, error_lvl) << "Read: " << std::strerror(errno);
			break ;
		}
		case 0 :
		{
			std::cerr << "Cgi Pipe empty - done reading\n";
			make_complete();
			break ;
		}
		default :
		{
			try {
				_parser.parse(read_buff, bytes_read);
				if (bytes_read < FILE_READ_BUF_SIZE)
				{
					std::cerr << "Read less than Buf_Size\n";
					// make_complete();
					
				}
			}
			catch (const HttpException & e)
			{
				manage_error(e.get_code_index());
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
		ssize_t len = write(_server_write_pipe, &(_request.get_body()[_written_size]), _request.bodysize() - _written_size);
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
	int ret = dup2(_server_read_pipe, _response.get_handler_fd()); // Now we want our server to React to ReadEvents to get the CGI output
	if (ret < 0)
	{
		manage_error();
		Logger(LOG_FILE, error_type, error_lvl) << "dup2: " << std::strerror(errno);
	}
	else
	{
		close(_server_read_pipe);
		_server_read_pipe = _response.get_handler_fd();
		_server_write_pipe = 0; // The fd was closed by call to dup2()
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
	// PHP CGI specific
	_env.add_cgi_env_var("REDIRECT_STATUS", "1");
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
		close(_server_write_pipe);
		close(_server_read_pipe);
		int ret = dup2(_cgi_read_pipe, STDIN_FILENO);
		if (ret < 0)
		{
			exit(EXIT_FAILURE);
		}
		close(_cgi_read_pipe);
		ret = dup2(_cgi_write_pipe, STDOUT_FILENO);
		if (ret < 0)
		{
			exit(EXIT_FAILURE);
		}
		close(_cgi_write_pipe);
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
			
			std::string root = _request.get_config()->root();
			if (int ret = chdir(root.c_str()) < 0)
			{
				Logger(LOG_FILE, error_type, error_lvl) << "Chdir: " << std::strerror(errno);
				exit(EXIT_FAILURE);
			}

			std::cerr << "Cgi params: bin: " << cgi_bin << " : req file path: " << _response.get_path() << '\n';
			execve(cgi_bin.c_str(), av, _env.get_cgi_env()); // /!\ For now, won't generate any cmd line arguments, seems like it should work without it
		}
		Logger(LOG_FILE, error_type, error_lvl) << "Execve: " << std::strerror(errno);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(_cgi_read_pipe);
		_cgi_read_pipe = 0;
		close(_cgi_write_pipe);
		_cgi_write_pipe = 0;
	}
}

void
CgiHandler::manage_error(StatusCodes::status_index_t error)
{
	close_pipes();
	if (!_response.metadata_sent())
	{
		_response.http_error(error);
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
				Logger(LOG_FILE, error_type, error_lvl) << "CGI error - exit status: " << WEXITSTATUS(status);
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
	int pipe_two[2];
	int ret = pipe(pipe_two);
	if (ret < 0)
	{
		close_pipes();
		Logger(LOG_FILE, error_type, error_lvl) << "Pipe: " << std::strerror(errno);
		return false;
	}
	_server_read_pipe = pipe_two[0];
	_cgi_write_pipe = pipe_two[1];
	return true;
}

bool
CgiHandler::set_nonblock(void)
{
	int ret = fcntl(_server_write_pipe, F_SETFL, O_NONBLOCK);
	if (ret == -1)
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Fcntl: " << std::strerror(errno);
		return false;
	}
	ret = fcntl(_server_read_pipe, F_SETFL, O_NONBLOCK);
	if (ret == -1)
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Fcntl: " << std::strerror(errno);
		return false;
	}
	return true;
}

//Only close an FD if it's value is != from 0 and != from _cgi_fd_handle
void
CgiHandler::close_pipes(void)
{
	if (_server_read_pipe != 0 && _server_read_pipe != _response.get_handler_fd())
	{
		close(_server_read_pipe);
		_server_read_pipe = 0;
	}
	if (_server_write_pipe != 0 && _server_write_pipe != _response.get_handler_fd())
	{
		close(_server_write_pipe);
		_server_write_pipe = 0;
	}
	if (_cgi_read_pipe != 0 && _cgi_read_pipe != _response.get_handler_fd())
	{
		close(_cgi_read_pipe);
		_cgi_read_pipe = 0;
	}
	if (_cgi_write_pipe != 0&& _cgi_write_pipe != _response.get_handler_fd())
	{
		close(_cgi_write_pipe);
		_cgi_write_pipe = 0;
	}
}