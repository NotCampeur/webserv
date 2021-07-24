#ifndef WEBSERV_CLIENT_HPP
# define WEBSERV_CLIENT_HPP

# include "webserv.hpp"
# include "ServerConfig.hpp"

class Client
{
    private:
        const int               _sockfd;
        const struct sockaddr * _address;
		const std::string		_ip;
		const ServerConfig &	_server_config;

    public:
        Client(int sockfd, struct sockaddr *address, const ServerConfig & config);
        ~Client(void);


        int     				getsockfd(void) const;
		const std::string & 	getip(void) const;
		const ServerConfig &	get_server_config(void) const;

    private:
        Client(void);
		Client(Client const & src);	
        Client &  operator=(Client const & src);
};

#endif
