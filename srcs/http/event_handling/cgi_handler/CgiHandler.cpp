#include "CgiHandler.hpp"
#include "InitiationDispatcher.hpp"
#include "Utils.hpp"
#include "Mime.hpp"
#include "unistd.h"
#include "SystemException.hpp"

CgiHandler::CgiHandler(Request & req, Response & resp, std::string client_ip, std::string method) :
_request(req),
_response(resp),
_event_flag(POLLOUT),
_method(method)
{
	set_environment();
	int ret = pipe(_pipe_fd);
	if (ret < 0)
	{
		throw SystemException("pipe error");
	}
}

CgiHandler::~CgiHandler(void)
{}



void 
CgiHandler::readable(void)
{}

void
CgiHandler::writable(void)
{
	
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
CgiHandler::get_write_fd(void) const
{
	return _pipe_fd[1];
}

void
CgiHandler::set_environment(void)
{
	std::string file_ext = Utils::get_file_ext(_response.get_path());

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
			const std::string *mime_ext = Mime::get_content_type(file_ext);
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
	if (_request.get_server_config().get_cgi_path(file_ext))
	{
		_env.add_cgi_env_var("SCRIPT_NAME", *_request.get_server_config().get_cgi_path(file_ext));
	}
	else
	{
		_env.add_cgi_env_var("SCRIPT_NAME", "NULL");
	}
	_env.add_cgi_env_var("SERVER_PORT", _request.get_server_config().get_port());
	_env.add_cgi_env_var("SERVER_PROTOCOL", "HTTP/1.1");
	_env.add_cgi_env_var("SERVER_SOFTWARE", "webserv/1.0");
}

// void
// CgiHandler::manage_error(void)
// {
// 	if (!_response.metadata_sent())
// 		_response.http_error(StatusCodes::INTERNAL_SERVER_ERROR_500);
// }

// void
// CgiHandler::response_complete(void)
// {
// 	_response.ready_to_send() = true;
// 	_response.complete() = true;
// }
