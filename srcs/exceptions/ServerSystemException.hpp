#ifndef WEBSERV_SERVERSystemException_H
# define WEBSERV_SERVERSystemException_H

# include "webserv.hpp"
# include "SystemException.hpp"

class ServerSystemException : public SystemException
{
	public:

    	ServerSystemException(const char *str, const std::string & ip, int port) throw();
    	ServerSystemException(ServerSystemException const & src) throw();
    	~ServerSystemException(void) throw();

		const char * what(void) const throw();

	private:
		ServerSystemException(void) throw();
		ServerSystemException &  operator=(ServerSystemException const & src) throw();
};

#endif
