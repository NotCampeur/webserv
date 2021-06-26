#include "Client.hpp"

Client::Client(int sockfd, struct sockaddr *address) : 
_sockfd(sockfd),
_address(address),
_requests(new request_queue())
{}

//Soft copy, consider removing
Client::Client(Client const & src) :
_sockfd(src._sockfd),
_address(src._address),
_requests(src._requests)
{}

Client::~Client(void)
{
    close(_sockfd);
    delete _address;

    size_t queue_size = _requests->size();
    for (size_t i = 0; i < queue_size; i++)
    {
        delete _requests->front();
    }
    delete _requests;
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

void
Client::add_request(Request * req)
{
    _requests->push(req);
}

Request *
Client::latest_request(void) const
{
    return _requests->back();
}

bool
Client::no_request(void) const
{
    return _requests->empty();
}