#ifndef SERVERHANDLER_H
# define SERVERHANDLER_H

# include "IEventHandler.hpp"
# include "HandlerTable.hpp"
// Include path TBU once makefile is fixed
# include "../Server/Server2.hpp"

class ServerHandler : public IEventHandler
{

    public:

        ServerHandler(int fd, const Server2 & server, const HandlerTable & ht);
        ServerHandler(ServerHandler const & src);
        ~ServerHandler(void);

        ServerHandler &  operator=(ServerHandler const & src);

        virtual void readable(void);
        virtual void writable(void);

        int getfd(void) const;

    private:
        ServerHandler(void);
 
        const int               _fd;
        const Server2 &         _server;
        const HandlerTable &    _ht;

};

#endif
