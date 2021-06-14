#include "ServerHandler.hpp"

ServerHandler::ServerHandler(const Server & server, InitiationDispatcher & idis) :
_server(server),
_idis(idis)
{}


ServerHandler::~ServerHandler(void)
{
	delete &_server;
}

ServerHandler &
ServerHandler::operator=(ServerHandler const & src)
{
	(void)src;
    // Cannot copy const value, remove operator?
    return *this;
}

void
ServerHandler::readable(void)
{
	socklen_t sockaddr_size = sizeof(struct sockaddr);

	while (1)
	{
		struct sockaddr * address = new (struct sockaddr);
		int ret = accept(get_serverfd(), address, &sockaddr_size);
		if (ret >= 0)
		{
			Client * client = new Client(ret, address);
			#ifdef DEBUG
				std::cout << "A new connection has been accepted on fd : " << ret << std::endl;
			#endif
			_idis.add_handle(*client);
		}
		else
		{
			delete address;
			if (errno != EWOULDBLOCK)
				throw UnableToAcceptConnection(ret);
			break ;
		}
	}
	#ifdef DEBUG
		std::cout << "Accept backlog of server " << _server.getsockfd() << " is empty" << std::endl;
	#endif
}

// No writable action can be detected on a server socket, hence this function does not do anything
void
ServerHandler::writable(void)
{}


int
ServerHandler::get_serverfd(void) const
{
    return _server.getsockfd();
}

const char *
ServerHandler::UnableToAcceptConnection::what() const throw()
{
	std::ostringstream oss;
	oss << "Accept error: " << _error << " : errno : " << strerror(errno) << std::endl;
	
	return oss.str().c_str();
}