#ifndef WEBSERV_SERVER_HPP
# define WEBSERV_SERVER_HPP

# include "webserv.hpp"
# include "webserv_param.hpp"

class Server
{
	private:
		
		int					_listening_port;
		int					_sockfd;
		struct sockaddr_in  _address;

	public:
		// With port 0, the OS assigns the port
		Server(int port, u_int32_t ip = INADDR_ANY, int domain = AF_INET, int sock_protocol = SOCK_STREAM);
		Server(Server const & src);

		// Need to unlink socket here
		~Server(void);

		int	getsockfd() const;
		Server &  operator=(Server const & src);

	private:
		Server(void);

		void				create_socket(int domain, int type, int protocol = 0);
		void				make_nonblocking();		
		void				init_addr_inputs(int domain, int port, u_int32_t ip);
		void				name_serv_socket();
		void				set_sock_opt();
		void				set_listener();

	// Class Exceptions:

	public:
		class UnableToCreateServerSocket : public std::exception
		{
				std::string	_msg;
			public:
				UnableToCreateServerSocket() throw();
				~UnableToCreateServerSocket() throw();
				const char * what(void) const throw();
		};

		class UnableToNameSocket : public std::exception
		{
				std::string	_msg;
			public:
				UnableToNameSocket() throw();
				~UnableToNameSocket() throw();
				const char * what(void) const throw();
		};

		class UnableToSetListener : public std::exception
		{
				std::string	_msg;
			public:
				UnableToSetListener() throw();
				~UnableToSetListener() throw();
				const char * what(void) const throw();
		};

		class UnableToSetNonblockFlag : public std::exception
		{
				std::ostringstream	_msg;
				int					_fd;
			public:
				UnableToSetNonblockFlag() throw();
				UnableToSetNonblockFlag(int fd) throw();
				UnableToSetNonblockFlag(const UnableToSetNonblockFlag & to_copy) throw();
				~UnableToSetNonblockFlag() throw();
				const char *what() const throw();
		};

		class UnableToSetSockOpt : public std::exception
		{
			const char * what() const throw();
		};
};

#endif