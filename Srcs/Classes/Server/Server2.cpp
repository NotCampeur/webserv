#include "Server2.hpp"

Server2::Server2(int port, u_int32_t ip = INADDR_ANY, int com_domain = AF_INET, int sock_type = SOCK_STREAM)
{
    create_socket(com_domain, sock_type);
    init_addr_inputs(com_domain, port, ip);
    name_serv_socket();
    set_listener();
}

Server2::Server2(Server2 const & src)
{
    (void)src;
}

Server2::~Server2(void) {}

Server2 &
Server2::operator=(Server2 const & src)
{
    return (*this);
}

int
Server2::getfd() const
{
	return (_fd);
}


void
Server2::create_socket(int domain, int type, int protocol = 0)
{
	int	reuse = 0;
	int	result = 0;
	
	this->_fd = socket(domain, type, protocol);
	result = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
	if (result == -1 || _fd == -1)
		throw UnableToCreateServerSocket();
	#ifdef DEBUG
		std::cout << "The server socket's fd is " << _socket << std::endl;
	#endif
}

void
Server2::make_nonblocking()
{
	int ret = fcntl(_fd, F_SETFL, O_NONBLOCK);
	if (ret == -1)
		throw
}

void
Server2::init_addr_inputs(int domain, int port, u_int32_t ip)
{
	_address.sin_family = domain;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = ip;
    std::memset(_address.sin_zero, 0, 8);
}

void
Server2::name_serv_socket()
{
	int	binding;

	binding = bind(_fd, (struct sockaddr *)&_address, sizeof(_address));
	if (binding == -1)
		throw UnableToNameSocket();
	#ifdef DEBUG
		std::cout << "The bind with the server is up" << std::endl;
	#endif
}

void
Server2::set_listener()
{
	int	open_to_connection(0);

	open_to_connection = listen(_fd, MAX_PENDING_CONNECTION);
	if (open_to_connection == -1)
		throw UnableToSetListener();
	#ifdef DEBUG
		std::cout << "The server socket is listening\n" << std::endl;
	#endif
}

const char *
Server2::UnableToSetNonblockFlag::what() const throw()
{
	std::ostringstream ss;

	ss << "cannot set nonblocking flag on fd " << _fd << " : error : " << errno << std::endl;
	return ss.str().c_str();
}