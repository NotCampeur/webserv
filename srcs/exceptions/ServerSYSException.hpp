#ifndef WEBSERV_SERVERSYSEXCEPTION_H
# define WEBSERV_SERVERSYSEXCEPTION_H

# include "webserv.hpp"
# include "SYSException.hpp"

class ServerSYSException : public SYSException
{
	public:

    	ServerSYSException(const char *str, const std::string & ip, int port) throw();
    	ServerSYSException(ServerSYSException const & src) throw();
    	~ServerSYSException(void) throw();

		const char * what(void) const throw();

	private:
		ServerSYSException(void) throw();
		ServerSYSException &  operator=(ServerSYSException const & src) throw();
};

#endif
