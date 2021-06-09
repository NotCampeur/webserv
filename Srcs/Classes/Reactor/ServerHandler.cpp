#include "ServerHandler.hpp"

ServerHandler::ServerHandler(int fd, const Server2 & server, const HandlerTable & ht) :
_fd(fd),
_server(server),
_ht(ht)
{}

ServerHandler::ServerHandler(ServerHandler const & src) :
_fd(src._fd),
_server(src._server),
_ht(src._ht)
{}

ServerHandler::~ServerHandler(void) {}

ServerHandler &
ServerHandler::operator=(ServerHandler const & src)
{
    // Cannot copy const value, remove operator?
    return *this;
}

void
ServerHandler::readable(void)
{
	int	addr_len = sizeof(_server);
	


	_client_socket.push_back(accept(_socket, (struct sockaddr *)&_address, (socklen_t *)&addr_len));
	if (_client_socket.back() == -1)
		throw UnableToAcceptConnection();
	#ifdef DEBUG
		std::cout << "A new connection has been acepted on fd : " << _client_socket.back() << std::endl;
	#endif
}  
}

void
ServerHandler::writable(void)
{

}


int
ServerHandler::getfd(void) const
{
    return this->_fd;
}