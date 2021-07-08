#include "Exception.hpp"

Exception::Exception(char *str) :
_msg(std::string(str))
{}

Exception::Exception(Exception const & src) :
_msg(src._msg)
{}

Exception::~Exception(void) {}

Exception &
Exception::operator=(Exception const & src)
{
	_msg = src._msg;
    return (*this);
}

const char *
Exception::what(void) const throw()
{
	return _msg.c_str();
}