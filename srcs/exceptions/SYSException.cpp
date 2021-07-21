#include "SYSException.hpp"

SYSException::SYSException(const char *str) throw() :
_msg(str),
_errno(errno)
{
	_msg += ": ";
	_msg += std::strerror(_errno);
}

SYSException::SYSException(SYSException const & src) throw() :
_msg(src._msg),
_errno(src._errno)
{}

SYSException::~SYSException(void) throw() {}

const char *
SYSException::what(void) const throw()
{
	return (_msg.c_str());
}