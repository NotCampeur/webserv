#include "Request.hpp"
#include "StatusCodes.hpp"

Request::Request(const config_type & server_configs)
: _complete(false),
_method(NULL),
_server_configs(server_configs),
_server_config_cache(NULL),
_config(NULL)
{}

Request::Request(Request const & src)
: _complete(src._complete)
, _method(src._method)
, _uri(src._uri)
, _headers(src._headers)
, _body(src._body)
, _server_configs(src._server_configs)
, _config(src._config)
{}

Request::~Request(void)
{
	if (_config != NULL)
		delete _config;
}

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
	if (_body.size() == server_config().max_client_body_size())
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
	_server_config_cache = NULL;
	// _cookies.clear();
}

void
Request::add_header(std::string & field_name, std::string & field_value)
{
	_headers.insert(std::pair<std::string, std::string>(field_name, field_value));
}

RequestConfig *
Request::get_config(void) const
{
	return _config;
}

void
Request::set_config(RequestConfig * config)
{
	if (_config != NULL)
		delete _config;
	_config = config;
}

const ServerConfig &
Request::server_config(void) const
{
	if (_server_config_cache != NULL)
		return *_server_config_cache;

	std::string host;

	if (_headers.find("host") != _headers.end())	// Defensive: there should always be a host
	{
		host = _headers.find("host")->second;
		
		//Remove the port at the end of the host.
		size_t pos = host.find(":");
		if (pos != std::string::npos)
			host = host.substr(0, pos);
	}
	else
	{
		Logger(error_type, error_lvl) << "Host header file not found in Request::get_server_config()";
		host = "default";
	}
	if (_server_configs.find(host) != _server_configs.end())
	{
		_server_config_cache = const_cast<ServerConfig *>(&_server_configs.find(host)->second);
		return _server_configs.find(host)->second;
	}
	else
	{
		Logger(basic_type, debug_lvl) << "DEFAULT CONFIG SET: NAME: " << _server_configs.find("default")->second.name();

		_server_config_cache = const_cast<ServerConfig *>(&_server_configs.find("default")->second);
		return _server_configs.find("default")->second;
	}
}

//Useful to avoid setting server config cache variable when in need of error page before parsing of host header
const std::string *
Request::get_error_page(StatusCodes::status_index_t error) const
{
	if (_server_config_cache == NULL)
	{
		return _server_configs.find("default")->second.error_page_path(StatusCodes::get_code_value(error));
	}
	else
	{
		return _server_config_cache->error_page_path(StatusCodes::get_code_value(error));
	}
}