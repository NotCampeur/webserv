#include "Request.hpp"

Request::Request(void) :
_complete(false),
_method(NULL)
{
	_body.reserve(MAX_CLIENT_BODY_SIZE);
}

Request::Request(Request const & src) :
_complete(src._complete),
_method(src._method->create_v()),
_uri(src._uri),
_headers(src._headers),
_body(src._body)
{}

Request::~Request(void)
{
	delete _method;
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
	if (_body.size() == MAX_CLIENT_BODY_SIZE)
		throw HttpException(HttpException::REQUEST_ENTITY_TOO_LARGE_413);
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
	delete _method;
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