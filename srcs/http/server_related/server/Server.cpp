#include "Server.hpp"

Server::Server(int port, u_int32_t ip, int com_domain, int sock_type)
{
	create_socket(com_domain, sock_type);
	make_nonblocking();
	init_addr_inputs(com_domain, port, ip);
	name_serv_socket();
	set_sock_opt();
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
Server::create_socket(int domain, int type, int protocol)
{
	// int	reuse = 0;
	// int	result = 0;
	
	this->_sockfd = socket(domain, type, protocol);
 	if (_sockfd == -1)
		throw UnableToCreateServerSocket();
	Logger(LOG_FILE, basic_type, minor_lvl) << "The server socket's fd is " << _sockfd;
}

void
Server::make_nonblocking()
{
	int ret = fcntl(_sockfd, F_SETFL, O_NONBLOCK);
	if (ret == -1)
		throw UnableToSetNonblockFlag(_sockfd);
	Logger(LOG_FILE, basic_type, minor_lvl) << "fcntl call to set nonblocking flag returned " << ret;
}

void
Server::init_addr_inputs(int domain, int port, u_int32_t ip)
{
	_listening_port = port;
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
	Logger(LOG_FILE, basic_type, minor_lvl) << "Server socket " << _sockfd << " is bind";
}

void
Server::set_sock_opt()
{
	int result, reuse;
	result = setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
	if (result == -1)
		throw UnableToSetSockOpt();
	Logger(LOG_FILE, basic_type, minor_lvl) << "SO_REUSEADDR flag set on socket";
}


void
Server::set_listener()
{
	int	open_to_connection(0);

	open_to_connection = listen(_sockfd, MAX_PENDING_CONNECTION);
	if (open_to_connection == -1)
		throw UnableToSetListener();
	Logger(LOG_FILE, basic_type, minor_lvl) << "The server socket is listening on " << _listening_port;
}

// EXCEPTIONS

Server::UnableToCreateServerSocket::UnableToCreateServerSocket() throw()
: _msg("Unable to create a socket for the server : ")
{
	_msg += strerror(errno);
}

Server::UnableToCreateServerSocket::~UnableToCreateServerSocket()  throw()
{}

const char *
Server::UnableToCreateServerSocket::what() const throw()
{
	return _msg.c_str();
}

Server::UnableToNameSocket::UnableToNameSocket() throw()
: _msg("Unable to name the socket of the server : ")
{
	_msg += strerror(errno);
}

Server::UnableToNameSocket::~UnableToNameSocket()  throw()
{}

const char *
Server::UnableToNameSocket::what() const throw()
{
	return _msg.c_str();
}

Server::UnableToSetListener::UnableToSetListener() throw()
: _msg("Unable to set socket as listener : ")
{
	_msg += strerror(errno);
}

Server::UnableToSetListener::~UnableToSetListener() throw()
{}

const char *
Server::UnableToSetListener::what() const throw()
{
	return _msg.c_str();
}

Server::UnableToSetNonblockFlag::UnableToSetNonblockFlag() throw()
: _msg("cannot set nonblocking flag on fd"), _fd(-1)
{
	_msg << " : " << strerror(errno);
}

Server::UnableToSetNonblockFlag::UnableToSetNonblockFlag(int fd) throw()
: _msg("cannot set nonblocking flag on fd : "), _fd(fd)
{
	_msg << _fd << " : " << strerror(errno);
}

Server::UnableToSetNonblockFlag::UnableToSetNonblockFlag(const UnableToSetNonblockFlag & to_copy) throw()
{
	_fd = to_copy._fd;
	_msg << to_copy._msg.str();
}

Server::UnableToSetNonblockFlag::~UnableToSetNonblockFlag() throw()
{}

const char *
Server::UnableToSetNonblockFlag::what() const throw()
{
	return _msg.str().c_str();
}
const char *
Server::UnableToSetSockOpt::what() const throw()
{
	return "Unable to set socket option";
}