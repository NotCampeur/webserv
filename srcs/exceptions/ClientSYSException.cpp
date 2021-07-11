#include "ClientSYSException.hpp"

ClientSYSException::ClientSYSException(const char *str, const std::string & ip, int fd) throw() :
SYSException(str),
_fd(fd)
{
	_msg += ": client address: ";
	_msg += ip;
}

ClientSYSException::ClientSYSException(ClientSYSException const & src) throw() :
SYSException(src),
_fd(src._fd)
{}

ClientSYSException::~ClientSYSException(void) throw() {}

const char *
ClientSYSException::what(void) const throw()
{
	return (_msg.c_str());
}

int
ClientSYSException::getfd(void) const throw()
{
	return _fd;
}