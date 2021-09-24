#include "Client.hpp"

Client::Client(int sockfd, struct sockaddr *address, const std::string & server_ip, const config_type & config) :
_sockfd(sockfd),
_address(address),
_ip(inet_ntoa((reinterpret_cast<sockaddr_in *>(address))->sin_addr)),
_server_ip(server_ip),
_server_config(config)
{
	std::stringstream ss;
	ss << (reinterpret_cast<sockaddr_in *>(address))->sin_port;
	_port = ss.str();
}


Client::~Client(void)
{
    close(_sockfd);
    delete _address;
}

int
Client::getsockfd(void) const
{
    return _sockfd;
}

const std::string &
Client::getip(void) const
{
	return _ip;
}

const std::string &
Client::getport(void) const
{
	return _port;
}

const Client::config_type &
Client::get_server_config(void) const
{
	return _server_config;
}

const std::string &
Client::get_server_ip(void) const
{
	return _server_ip;
}