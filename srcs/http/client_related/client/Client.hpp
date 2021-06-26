#ifndef WEBSERV_CLIENT_HPP
# define WEBSERV_CLIENT_HPP

# include "webserv.hpp"
# include <queue>
# include "Request.hpp"

class Client
{
    public:
        typedef std::queue<Request *>   request_queue;

    private:
        const int               _sockfd;
        const struct sockaddr * _address;
        request_queue           *_requests;

    public:
        Client(int sockfd, struct sockaddr *address);
        Client(Client const & src);
        ~Client(void);

        Client &  operator=(Client const & src);

        int     getsockfd(void) const;

        void    add_request(Request * req);
        bool    no_request(void) const;
        Request *latest_request(void) const;

    private:
        Client(void);

};

#endif
