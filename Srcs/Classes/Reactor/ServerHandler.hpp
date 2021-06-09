#ifndef SERVERHANDLER_H
# define SERVERHANDLER_H

# include "IEventHandler.hpp"

class ServerHandler : public IEventHandler
{

    public:

        ServerHandler(int fd);
        ServerHandler(ServerHandler const & src);
        ~ServerHandler(void);

        ServerHandler &  operator=(ServerHandler const & src);

        virtual void readable(void);
        virtual void writable(void);

        int getfd(void) const;

    private:
        ServerHandler(void);
 
        const int _fd;

};

#endif
