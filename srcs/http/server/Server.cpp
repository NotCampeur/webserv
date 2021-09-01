#include "Server.hpp"

Server::Server(ServerConfig *config, int com_domain, int sock_type) :
_config()
{
	_config.insert(std::pair<std::string, const ServerConfig &>(config->name(), *config));
	create_socket(com_domain, sock_type);
	make_nonblocking();
	set_sock_opt();
	init_addr_inputs(com_domain, atoi(config->port().c_str()), inet_addr(config->ip().c_str()));
	name_serv_socket();
	set_listener();

	_ip = std::string(inet_ntoa(_address.sin_addr));
}

Server::~Server(void)
{
	close(_sockfd);
	Server::config_type::iterator it = _config.begin();
	for (; it != _config.end(); ++it)
		delete &it->second;
}

// Server &
// Server::operator=(Server const & src)
// {
// 	this->_sockfd = src._sockfd;
// 	this->_address = src._address;
// 	return (*this);
// }

int
Server::getsockfd() const
{
	return (_sockfd);
}

void
Server::create_socket(int domain, int type, int protocol)
{
	this->_sockfd = socket(domain, type, protocol);
 	if (_sockfd == -1)
	{
		delete &_config;
		throw SystemException("Unable to create server socket");
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "The server socket's fd is " << _sockfd;
}

void
Server::make_nonblocking()
{
	int ret = fcntl(_sockfd, F_SETFL, O_NONBLOCK);
	if (ret == -1)
	{
		delete &_config;
		throw SystemException("Cannot set nonblocking flag on server socket");
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "fcntl call to set nonblocking flag returned " << ret;
}


void
Server::set_sock_opt()
{
	int enable = 1;
	int result = setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	if (result == -1)
	{
		delete &_config;
		throw SystemException("Unable to set socket option");
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "SO_REUSEADDR flag set on socket";
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
	{
		delete &_config;
		throw SystemException("Unable to name the server socket");
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "Server socket " << _sockfd << " is bind";
}

void
Server::set_listener()
{
	int	open_to_connection(0);

	open_to_connection = listen(_sockfd, MAX_PENDING_CONNECTION);
	if (open_to_connection == -1)
	{
		delete &_config;
		throw SystemException("Unable to set socket as listener");
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "The server socket is listening on " << getport();
}

int
Server::getport(void) const
{
	return _address.sin_port;
}

const std::string &
Server::getip(void) const
{
	return _ip;
}

const Server::config_type &
Server::get_server_config(void) const
{
	return _config;
}

void
Server::add_server_config(const ServerConfig &config)
{
	std::pair<Server::config_type::iterator, bool> result;
	result = _config.insert(std::pair<std::string, const ServerConfig &>(config.name(), config));
	if (result.second == false)
		throw Exception("Servers must be differentiable (By name or by IP or by port).");
}
