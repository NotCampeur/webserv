#include "ServerSystemException.hpp"

ServerSystemException::ServerSystemException(const char *str, const std::string & ip, int port) throw() :
SystemException(str)
{
	_msg += ": server address: ";
	_msg += ip;
	_msg += ':';
	_msg += port;
}

ServerSystemException::ServerSystemException(ServerSystemException const & src) throw() :
SystemException(src)
{}

ServerSystemException::~ServerSystemException(void) throw() {}

const char *
ServerSystemException::what(void) const throw()
{
	return (_msg.c_str());
}