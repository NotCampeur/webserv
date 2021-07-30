#include "HttpException.hpp"

HttpException::HttpException(StatusCodes::status_index_t error) throw():
_index(error)
{}

HttpException::~HttpException(void) throw() {}

HttpException::HttpException(HttpException const & src) throw() :
_index(src._index)
{}

StatusCodes::status_index_t
HttpException::get_error_index(void) const
{
	return _index;
}