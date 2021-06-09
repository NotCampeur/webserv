#ifndef SERVER2_H
# define SERVER2_H

# include "webserv.hpp"
# include "werbserv_param.hpp"

class Server2
{

    public:
        // With port 0, the OS assigns the port
        Server2(int port, int domain = AF_INET, int sock_protocol = SOCK_STREAM, u_int32_t ip = INADDR_ANY);
        Server2(Server2 const & src);

        // Need to unlink socket here
        ~Server2(void);

        Server2 &  operator=(Server2 const & src);

    private:
        Server2();

        int                 _fd;
        struct sockaddr_in  _address;

		void				create_socket(int domain, int type, int protocol = 0);
		void				init_addr_inputs(int domain, int port, u_int32_t ip);
		void				name_serv_socket();
		void				set_listener();

    public:
	
		class UnableToCreateServerSocket : public std::exception
		{
			public:
				UnableToCreateServerSocket() throw() {}
				~UnableToCreateServerSocket() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to create a socket for the server : ")
					+ std::string(strerror(errno)))).c_str();}
		};

		class UnableToNameSocket : public std::exception
		{
			public:
				UnableToNameSocket() throw() {}
				~UnableToNameSocket() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to name the socket of the server : ")
					+ std::string(strerror(errno)))).c_str();}
		};

		class UnableToSetListener : public std::exception
		{
			public:
				UnableToSetListener() throw() {}
				~UnableToSetListener() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to set socket as listener : ")
					+ std::string(strerror(errno)))).c_str();}
		};

};

#endif