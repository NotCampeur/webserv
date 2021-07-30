#include "ClientSystemException.hpp"

ClientSystemException::ClientSystemException(const char *str, const std::string & ip, int fd) throw() :
SystemException(str),
_fd(fd)
{
	_msg += ": client address: ";
	_msg += ip;
}

ClientSystemException::ClientSystemException(ClientSystemException const & src) throw() :
SystemException(src),
_fd(src._fd)
{}

ClientSystemException::~ClientSystemException(void) throw() {}

const char *
ClientSystemException::what(void) const throw()
{
	return (_msg.c_str());
}

int
ClientSystemException::getfd(void) const throw()
{
	return _fd;
}