#ifndef CLIENT_H
# define CLIENT_H

# include "webserv.hpp"

class Client
{

    private:

        const int               _fd;
        const struct sockaddr * _address;

    public:
        
        Client(int fd, struct sockaddr *address);
        Client(Client const & src);
        ~Client(void);

        Client &  operator=(Client const & src);

        int getfd(void) const;

    private:

        Client(void);

};

#endif
