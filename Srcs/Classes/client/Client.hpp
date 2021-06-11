#ifndef CLIENT_H
# define CLIENT_H

# include "webserv.hpp"

class Client
{

    private:

        const int               _sockfd;
        const struct sockaddr * _address;

    public:
        
        Client(int sockfd, struct sockaddr *address);
        Client(Client const & src);
        ~Client(void);

        Client &  operator=(Client const & src);

        int getsockfd(void) const;

    private:

        Client(void);

};

#endif
