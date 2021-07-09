#include "Request.hpp"

Request::Request(void) :
_complete(false),
_method(NULL),
_body_size(0)
{}

Request::Request(Request const & src) :
_complete(src._complete),
_uri(src._uri),
_headers(src._headers)
{}

Request::~Request(void)
{
	delete _method;
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
	return _body_size;
}

bool &
Request::complete(void)
{
	return _complete;
}

void
Request::add_char_to_body(char c)
{
	if (_body_size == MAX_CLIENT_BODY_SIZE)
		throw HttpException(::HttpException::REQUEST_ENTITY_TOO_LARGE_413);
	_body[_body_size] = c;
	_body_size++;
}

// To delete
void
Request::addbody(char *buf, size_t len)
{
	if ((_body_size + len) > MAX_CLIENT_BODY_SIZE)
		throw HttpException(REQUEST_ENTITY_TOO_LARGE_413);
	std::memcpy(&_body[_body_size], buf, len);
}

const char *
Request::get_body(void) const
{
	return &_body[0]; //To return _body directly, need to change return type to char const *
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
	_body_size = 0;
}

void
Request::add_header(std::string & field_name, std::string & field_value)
{
	_headers.insert(std::pair<std::string, std::string>(field_name, field_value));
}