#include "Exception.hpp"

Exception::Exception(const char *str) throw():
_msg(std::string(str))
{}

Exception::Exception(Exception const & src) throw():
_msg(src._msg)
{}

Exception::~Exception(void) throw() {}

Exception &
Exception::operator=(Exception const & src) throw()
{
	_msg = src._msg;
    return (*this);
}

const char *
Exception::what(void) const throw()
{
	return _msg.c_str();
}