#include "HttpException.hpp"

HttpException::HttpException(int error) :
_error(error)
{}

HttpException::HttpException(HttpException const & src) :
_error(src._error)
{}

HttpException::~HttpException(void) {}

HttpException &
HttpException::operator=(HttpException const & src)
{
	_error = src._error;
    return (*this);
}

int
HttpException::error_code(void)
{
	return _error;
}
