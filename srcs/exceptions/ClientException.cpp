#include "ClientException.hpp"

ClientException::ClientException(const char *str, const std::string & ip, int fd) throw() :
Exception(str),
_fd(fd)
{
	_msg += ": client address: ";
	_msg += ip;
}

ClientException::ClientException(ClientException const & src) throw() :
Exception(src),
_fd(src._fd)
{}

ClientException::~ClientException(void) throw() {}

const char *
ClientException::what(void) const throw()
{
	return (_msg.c_str());
}

int
ClientException::getfd(void) const throw()
{
	return _fd;
}