#include "ServerHandler.hpp"

ServerHandler::ServerHandler(const Server & server, HandlerTable & ht) :
_server(server),
_ht(ht)
{}

ServerHandler::ServerHandler(ServerHandler const & src) :
_server(src._server),
_ht(src._ht)
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
			new_client_handler(*client);
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
		std::cout << "Accept backlog is empty" << std::endl;
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

void
ServerHandler::new_client_handler(Client & client)
{
	ClientHandler *ch = new ClientHandler(client, _ht);
	_ht.add(client.getsockfd(), *ch);
}

const char *
ServerHandler::UnableToAcceptConnection::what() const throw()
{
	std::ostringstream oss;
	oss << "Accept error: " << _error << " : errno : " << strerror(errno) << std::endl;
	
	return oss.str().c_str();
}