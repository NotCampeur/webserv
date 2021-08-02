#include "SystemException.hpp"

SystemException::SystemException(const char *str) throw() :
_msg(str),
_errno(errno)
{
	_msg += ": ";
	_msg += std::strerror(_errno);
}

SystemException::SystemException(SystemException const & src) throw() :
_msg(src._msg),
_errno(src._errno)
{}

SystemException::~SystemException(void) throw() {}

const char *
SystemException::what(void) const throw()
{
	return (_msg.c_str());
}