#include "ClientHandler.hpp"

ClientHandler::ClientHandler(void) {}

ClientHandler::ClientHandler(ClientHandler const & src)
{
    (void)src;
}

ClientHandler::~ClientHandler(void) {}

ClientHandler &
ClientHandler::operator=(ClientHandler const & src)
{
    return (*this);
}
