#ifndef SERVER_H
# define SERVER_H

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
		void				set_listener();

	// Class Exceptions:

	public:
		class UnableToCreateServerSocket : public std::exception
		{
			const char *what() const throw();
		};

		class UnableToNameSocket : public std::exception
		{
			const char *what() const throw();
		};

		class UnableToSetListener : public std::exception
		{
				const char *what() const throw();
		};

		class UnableToSetNonblockFlag : public std::exception
		{
			public:
				UnableToSetNonblockFlag(int fd) throw() : _fd(fd) {}
			private:
				const char *what() const throw();
				int			_fd;
		};
};

#endif