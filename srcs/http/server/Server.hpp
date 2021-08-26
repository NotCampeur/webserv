#ifndef WEBSERV_SERVER_HPP
# define WEBSERV_SERVER_HPP

# include "webserv.hpp"
# include "webserv_param.hpp"
# include "SystemException.hpp"
# include "ServerConfig.hpp"

class Server
{
	public:
		typedef std::map<std::string, const ServerConfig &>	config_type;

	private:
		int					_sockfd;
		struct sockaddr_in	_address;
		std::string			_ip;
		config_type			_config;

	public:
		// With port 0, the OS assigns the port
		Server(ServerConfig *config, int domain = AF_INET, int sock_protocol = SOCK_STREAM);
		~Server(void);


		int					getsockfd(void) const;
		int					getport(void) const;
		const std::string &	getip(void) const;
		const config_type &	get_server_config(void) const;
		void				add_server_config(const ServerConfig &config);

	private:
		Server(void);
		Server(Server const & src);
		Server &  operator=(Server const & src);

		void				create_socket(int domain, int type, int protocol = 0);
		void				make_nonblocking(void);		
		void				init_addr_inputs(int domain, int port, u_int32_t ip);
		void				name_serv_socket(void);
		void				set_sock_opt(void);
		void				set_listener(void);
};

#endif