#include "Server.hpp"

Server::Server(int port, u_int32_t ip = INADDR_ANY, int com_domain = AF_INET, int sock_type = SOCK_STREAM)
{
    create_socket(com_domain, sock_type);
	make_nonblocking();
    init_addr_inputs(com_domain, port, ip);
    name_serv_socket();
    set_listener();
}

Server::Server(Server const & src)
{
    (void)src;
}

Server::~Server(void)
{
	close(_sockfd);
}

Server &
Server::operator=(Server const & src)
{
	this->_sockfd = src._sockfd;
	this->_address = src._address;
    return (*this);
}

int
Server::getsockfd() const
{
	return (_sockfd);
}

void
Server::create_socket(int domain, int type, int protocol = 0)
{
	int	reuse = 0;
	int	result = 0;
	
	this->_sockfd = socket(domain, type, protocol);
	result = setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
	if (result == -1 || _sockfd == -1)
		throw UnableToCreateServerSocket();
	#ifdef DEBUG
		DEBUG_STREAM << "The server socket's fd is " << _socket << std::endl;
	#endif
}

void
Server::make_nonblocking()
{
	int ret = fcntl(_sockfd, F_SETFL, O_NONBLOCK);
	if (ret == -1)
		throw UnableToSetNonblockFlag(_sockfd);
	#ifdef DEBUG
		DEBUG_STREAM << "fcntl call to set nonblocking flag returned " << ret << std::endl;
	#endif
}

void
Server::init_addr_inputs(int domain, int port, u_int32_t ip)
{
	_address.sin_family = domain;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = ip;
    std::memset(_address.sin_zero, 0, 8);
}

void
Server::name_serv_socket()
{
	int	binding;

	binding = bind(_sockfd, (struct sockaddr *)&_address, sizeof(_address));
	if (binding == -1)
		throw UnableToNameSocket();
	#ifdef DEBUG
		DEBUG_STREAM << "The bind with the server is up" << std::endl;
	#endif
}

void
Server::set_listener()
{
	int	open_to_connection(0);

	open_to_connection = listen(_sockfd, MAX_PENDING_CONNECTION);
	if (open_to_connection == -1)
		throw UnableToSetListener();
	#ifdef DEBUG
		DEBUG_STREAM << "The server socket is listening\n" << std::endl;
	#endif
}

// EXCEPTIONS

const char *
Server::UnableToCreateServerSocket::what() const throw()
{
	std::string err = "Unable to create a socket for the server : ";
	err += strerror(errno);

	return err.c_str();
}

const char *
Server::UnableToNameSocket::what() const throw()
{
	std::string err = "Unable to name the socket of the server : ";
	err += strerror(errno);

	return err.c_str();
}

const char *
Server::UnableToSetListener::what() const throw()
{
	std::string err = "Unable to set socket as listener : ";
	err += strerror(errno);

	return err.c_str();
}

const char *
Server::UnableToSetNonblockFlag::what() const throw()
{
	std::ostringstream ss;

	ss << "cannot set nonblocking flag on fd " << _fd << " : error : " << errno << std::endl;
	return ss.str().c_str();
}
