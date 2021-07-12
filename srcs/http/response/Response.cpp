#include "Response.hpp"

Response::Response(void) :
_version("HTTP/1.1"),
_ready(false)
{}

Response::Response(Response const & src) :
_buffer(src._buffer),
_version(src._version),
_ready(src._ready)
{
    (void)src;
}

Response::~Response(void) {}

Response &
Response::operator=(Response const & src)
{
	_buffer = src._buffer;
	_ready = src._ready;
    return (*this);
}


bool
Response::isready(void) const
{
	return _ready;
}

void
Response::set_readyness(bool b)
{
	_ready = b;
}

void
Response::fill_response(std::string &str)
{
	_buffer += str;
}

const std::string &
Response::get_response(void) const
{
	return _buffer;
}

void
Response::reset(void)
{
	_buffer.clear();
	_ready = false;
}