#ifndef WEBSERV_SERVER_HPP
# define WEBSERV_SERVER_HPP

# include "webserv.hpp"
# include "webserv_param.hpp"
# include "SystemException.hpp"
# include "ServerConfig.hpp"

class Server
{
	private:
		
		int					_sockfd;
		struct sockaddr_in  _address;
		std::string			_ip;
		ServerConfig		_config;

	public:
		// With port 0, the OS assigns the port
		Server(int port, u_int32_t ip = INADDR_ANY, int domain = AF_INET, int sock_protocol = SOCK_STREAM);
		Server(Server const & src);
		~Server(void);

		Server &  operator=(Server const & src);

		int						getsockfd(void) const;
		int						getport(void) const;
		const std::string &		getip(void) const;
		const ServerConfig &	get_server_config(void) const;

	private:
		Server(void);

		void				create_socket(int domain, int type, int protocol = 0);
		void				make_nonblocking(void);		
		void				init_addr_inputs(int domain, int port, u_int32_t ip);
		void				name_serv_socket(void);
		void				set_sock_opt(void);
		void				set_listener(void);
};

#endif