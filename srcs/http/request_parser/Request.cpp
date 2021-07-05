#include "Request.hpp"

Request::Request(void) : _complete(false)
{}

Request::Request(Request const & src) :
_complete(src._complete),
_http_method(src._http_method),
_http_version(src._http_version),
_uri(src._uri),
_headers(src._headers)
{}

Request::~Request(void) {}

std::string &
Request::method(void)
{
	return _http_method;
}

Request::uri_t &
Request::uri(void)
{
	return _uri;
}

std::string &
Request::version(void)
{
	return _http_version;
}

std::map<std::string, std::string> &
Request::headers(void)
{
	return _headers;
}

bool &
Request::complete(void)
{
	return _complete;
}

void
Request::reset(void)
{
	_complete = false;
	_http_method.clear();
	_uri.path.clear();
	_uri.query.clear();
	_uri.fragment.clear();
	_headers.clear();
}

void
Request::add_header(std::string & field_name, std::string & field_value)
{
	_headers.insert(std::pair<std::string, std::string>(field_name, field_value));
}