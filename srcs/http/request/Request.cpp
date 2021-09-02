#include "Request.hpp"

//TODO: Need to first check the headers to know the config to use.

Request::Request(const config_type & server_configs)
: _complete(false)
, _method(NULL)
, _config(NULL)
{
	// We need to initialize the headers.
	for (Request::config_type::const_iterator	it = server_configs.begin()
			; it != server_configs.end(); it++)
	{
		if (_headers["host"] == it->first + ":" + it->second.port())
		{
			*_config = it->second;
			Logger(LOG_FILE, basic_type, debug_lvl) << "Named Server config loaded";
			break;
		}
	}
}

Request::Request(Request const & src)
: _complete(src._complete)
, _method(src._method)
, _uri(src._uri)
, _headers(src._headers)
, _body(src._body)
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
	if (_body.size() == _config->max_client_body_size())
		throw HttpException(StatusCodes::REQUEST_ENTITY_TOO_LARGE_413);
	_body += c;
}

const std::string &
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

RequestConfig *
Request::config(void) const
{
	return _config;
}

void
Request::set_config(RequestConfig * config)
{
	_config = config;
}