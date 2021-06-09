#ifndef CLIENTHANDLER_H
# define CLIENTHANDLER_H

# include "IEventHandler.hpp"

class ClientHandler : public IEventHandler
{

public:

    ClientHandler(int fd);
    ClientHandler(ClientHandler const & src);
    ~ClientHandler(void);

    ClientHandler &  operator=(ClientHandler const & src);

private:
    ClientHandler(void);
    const int _fd;

};

#endif
