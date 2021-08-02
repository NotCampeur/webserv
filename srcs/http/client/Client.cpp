#include "Client.hpp"

Client::Client(int sockfd, struct sockaddr *address, const ServerConfig & config) :
_sockfd(sockfd),
_address(address),
_ip(inet_ntoa((reinterpret_cast<sockaddr_in *>(address))->sin_addr)),
_server_config(config)
{}


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

const ServerConfig &
Client::get_server_config(void) const
{
	return _server_config;
}
