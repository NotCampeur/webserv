#include "CgiHandler.hpp"
#include "InitiationDispatcher.hpp"
#include "Utils.hpp"
#include "Mime.hpp"
#include "unistd.h"
#include "SystemException.hpp"

CgiHandler::CgiHandler(Request & req, Response & resp, std::string method) :
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
	set_environment();
	int ret = pipe(_pipe_fd);
	if (ret < 0)
	{
		manage_error();
		Logger(LOG_FILE, error_type, error_lvl) << "Pipe: " << std::strerror(errno);
	}
	_response.set_handler_fd(_pipe_fd[1]);
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
		return ;
	}

	char		read_buff[FILE_READ_BUF_SIZE];
	ssize_t		bytes_read;

	bytes_read = read(_pipe_fd[1], read_buff, FILE_READ_BUF_SIZE);

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
			// std::cerr << "Cgi read buf:\n" << std::string(read_buff, bytes_read) << '\n';
			_parser.parse(read_buff, bytes_read);
			if (bytes_read < FILE_READ_BUF_SIZE)
			{
				std::cerr << "Read less than Buf_Size\n";
				make_complete();
			}
		}
	}
	// Logger(LOG_FILE, basic_type, minor_lvl) << "Socket content (" << bytes_read << " byte(s) read): " << std::string(read_buff, bytes_read);
}

void
CgiHandler::writable(void)
{
	if (_method == "POST" && _request.bodysize() > 0)
	{
		ssize_t len = write(_pipe_fd[1], &(_request.get_body()[_written_size]), _request.bodysize() - _written_size);
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
	_event_flag = POLLIN;
	start_cgi();
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

int
CgiHandler::get_fd(void) const
{
	return _pipe_fd[1];
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
	if (_request.get_server_config().get_cgi_path(_file_ext))
	{
		_env.add_cgi_env_var("SCRIPT_NAME", *_request.get_server_config().get_cgi_path(_file_ext));
	}
	else
	{
		_env.add_cgi_env_var("SCRIPT_NAME", "NULL");
	}
	_env.add_cgi_env_var("SERVER_PORT", _request.get_server_config().get_port());
	_env.add_cgi_env_var("SERVER_PROTOCOL", "HTTP/1.1");
	_env.add_cgi_env_var("SERVER_SOFTWARE", "webserv/1.0");
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
		int ret = dup2(_pipe_fd[0], STDIN_FILENO);
		if (ret < 0)
		{
			exit(EXIT_FAILURE);
		}
		ret = dup2(_pipe_fd[1], STDOUT_FILENO);
		if (ret < 0)
		{
			exit(EXIT_FAILURE);
		}

		const std::string *cgi_bin = _request.get_server_config().get_cgi_path(_file_ext);
		if (cgi_bin == NULL)
		{
			exit(EXIT_FAILURE);
		}
		else
		{
			// std::cerr << "Chile about to execve\n";
			execve(cgi_bin->c_str(), NULL, _env.get_cgi_env()); // /!\ For now, won't generate any cmd line arguments, seems like it should work without it
		}
		Logger(LOG_FILE, error_type, error_lvl) << "Execve: " << std::strerror(errno);
		exit(EXIT_FAILURE);
	}
	else
	{
		int ret = dup2(_pipe_fd[0], _pipe_fd[1]); // Replace write fd by read fd so we can keep using this object + closing write fd so that if there's an error in child, main process will get a "read event"
		if (ret < 0)
		{
			manage_error();
			Logger(LOG_FILE, error_type, error_lvl) << "Pipe: " << std::strerror(errno);
		}
		close (_pipe_fd[0]);
	}
	/*
	Need to waitpid (non-block) to check if errors occured and ensure clean termination of process
	Need to be able to kill the process if an error occurs (put in handler destructor)
	*/
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
				if(_response.metadata_sent())
				{
					make_complete();
				}
				else
				{
					_response.http_error(StatusCodes::INTERNAL_SERVER_ERROR_500);
				}
				return true;
			}
		}
	}
	return false;
}