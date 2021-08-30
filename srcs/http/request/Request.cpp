#include "Request.hpp"

//TODO: Need to first check the headers to know the config to use.

Request::Request(const Request::config_type & config) :
_complete(false),
_method(NULL),
_server_config(config)
{
	// Now using vectors along with push_back()
	// _body.reserve(_server_config.begin()->second.max_client_body_size());
}

Request::Request(Request const & src) :
_complete(src._complete),
_method(src._method),
_uri(src._uri),
_headers(src._headers),
_body(src._body),
_server_config(src._server_config)
{}

Request::~Request(void)
{}

void
Request::set_method(IHttpMethod *method)
{
	_method = method;
}

IHttpMethod &
Request::method(void)
{
	return *_method;
}

Request::uri_t &
Request::uri(void)
{
	return _uri;
}

std::map<std::string, std::string> &
Request::headers(void)
{
	return _headers;
}

size_t
Request::bodysize(void) const
{
	return _body.size();
}

bool &
Request::complete(void)
{
	return _complete;
}

void
Request::add_char_to_body(char c)
{
	
	if (_body.size() == get_server_config().get_max_client_body_size())
		throw HttpException(StatusCodes::REQUEST_ENTITY_TOO_LARGE_413);
	_body.push_back(c);
}

const std::vector<char> &
Request::get_body(void) const
{
	return _body;
}

void
Request::reset(void)
{
	_complete = false;
	_method = NULL;
	_uri.path.clear();
	_uri.query.clear();
	_uri.fragment.clear();
	_headers.clear();
	_body.clear();
}

void
Request::add_header(std::string & field_name, std::string & field_value)
{
	_headers.insert(std::pair<std::string, std::string>(field_name, field_value));
}

const ServerConfig &
Request::get_server_config(void) const
{
	std::string host;
	if (_headers.find("host") != _headers.end())	// Defensive: there should always be a host
	{
		host = _headers.find("host")->second;
	}
	else
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Host header file not found in Request::get_server_config()";
		host = "default";
	}

	if (_server_config.find(host) != _server_config.end())
	{
		return _server_config.find(host)->second;
	}
	else
	{
		// return _server_config.find("default")->second; 
		return _server_config.begin()->second; // TBU -> remove this line and uncomment the above once we're sure there'll always be a "default" config
	}
}