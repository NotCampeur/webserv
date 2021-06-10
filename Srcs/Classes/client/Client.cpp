#include "Client.hpp"

Client::Client(int fd, struct sockaddr *address) : 
_fd(fd),
_address(address)
{}

Client::Client(Client const & src) :
_fd(src._fd),
_address(src._address)
{}

Client::~Client(void) {}

Client &
Client::operator=(Client const & src)
{
    // Cannot copy constant attributes
    return (*this);
}

int
Client::getfd(void) const
{
    return _fd;
}