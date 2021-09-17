#include "HttpException.hpp"

HttpException::HttpException(StatusCodes::status_index_t error) throw() :
_index(error)
{}

HttpException::HttpException(StatusCodes::status_index_t redir_code, const std::string & location) throw() :
_index(redir_code),
_location(location)
{}

HttpException::~HttpException(void) throw() {}

HttpException::HttpException(HttpException const & src) throw() :
_index(src._index),
_location(src._location)
{}

StatusCodes::status_index_t
HttpException::get_code_index(void) const throw()
{
	return _index;
}

const std::string &
HttpException::get_location(void) const throw()
{
	return _location;
}
