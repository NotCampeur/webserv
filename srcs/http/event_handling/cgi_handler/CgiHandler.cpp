#include "CgiHandler.hpp"
#include "InitiationDispatcher.hpp"
#include "Utils.hpp"
#include "Mime.hpp"

CgiHandler::CgiHandler(const Request & req, Response & resp) :
_request(req),
_response(resp),
_event_flag(POLLIN)
{
	// Needs CGI path!!
	set_environment();
}

CgiHandler::~CgiHandler(void)
{}



void 
CgiHandler::readable(void)
{}

void
CgiHandler::writable(void)
{}

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
	// Gateway Interface
	_env.add_cgi_env_var("GATEWAY_INTERFACE", "CGI/1.1");

	// Path Info
	_env.add_cgi_env_var("PATH_INFO", _response.get_server_config().get_cgi_path())

		

	}

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
