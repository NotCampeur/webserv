#ifndef WEBSERV_CLIENT_HPP
# define WEBSERV_CLIENT_HPP

# include "webserv.hpp"
# include "ServerConfig.hpp"

class Client
{
	public:
		typedef std::map<std::string, const ServerConfig &> config_type;
    private:
        const int				_sockfd;
        const struct sockaddr *	_address;
		const std::string		_ip;
		const config_type &		_server_config;

    public:
        Client(int sockfd, struct sockaddr *address, const config_type & config);
        ~Client(void);


        int     					getsockfd(void) const;
		const std::string & 		getip(void) const;
		const config_type &	get_server_config(void) const;

    private:
        Client(void);
		Client(Client const & src);	
        Client &  operator=(Client const & src);
};

#endif
