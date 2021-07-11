#include "ServerSYSException.hpp"

ServerSYSException::ServerSYSException(const char *str, const std::string & ip, int port) throw() :
SYSException(str)
{
	_msg += ": server address: ";
	_msg += ip;
	_msg += ':';
	_msg += port;
}

ServerSYSException::ServerSYSException(ServerSYSException const & src) throw() :
SYSException(src)
{}

ServerSYSException::~ServerSYSException(void) throw() {}

const char *
ServerSYSException::what(void) const throw()
{
	return (_msg.c_str());
}