#include "Client.hpp"

Client::Client(int sockfd, struct sockaddr *address) : 
_sockfd(sockfd),
_address(address)
{}

Client::Client(Client const & src) :
_sockfd(src._sockfd),
_address(src._address)
{}

Client::~Client(void)
{
    close(_sockfd);
    delete _address;
}

Client &
Client::operator=(Client const & src)
{
	(void)src;
    // Cannot copy constant attributes
    return (*this);
}

int
Client::getsockfd(void) const
{
    return _sockfd;
}