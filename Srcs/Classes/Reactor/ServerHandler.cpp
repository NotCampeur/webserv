#include "ServerHandler.hpp"

ServerHandler::ServerHandler(int fd) : _fd(fd)
{}

ServerHandler::ServerHandler(ServerHandler const & src) : _fd(src._fd)
{}

ServerHandler::~ServerHandler(void) {}

ServerHandler &
ServerHandler::operator=(ServerHandler const & src)
{
    // Cannot copy const value
    return *this;
}

void
ServerHandler::readable(void)
{
    
}

void
ServerHandler::writable(void)
{

}


int
ServerHandler::getfd(void) const
{
    return this->_fd;
}