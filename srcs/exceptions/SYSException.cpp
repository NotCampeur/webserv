#include "SYSException.hpp"

SYSException::SYSException(char *str) :
_msg(str),
_errno(errno)
{
	_msg += ":";
	_msg += std::strerror(_errno);
}

SYSException::SYSException(SYSException const & src) :
_msg(src._msg),
_errno(src._errno)
{}

SYSException::~SYSException(void) {}

SYSException &
SYSException::operator=(SYSException const & src)
{
    return (*this);
}

const char *
SYSException::what(void) const throw()
{
	return (_msg.c_str());
}