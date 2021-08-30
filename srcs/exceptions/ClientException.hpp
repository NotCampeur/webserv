#ifndef WEBSERV_CLIENTEXCEPTION_H
# define WEBSERV_CLIENTEXCEPTION_H

# include "webserv.hpp"
# include "Exception.hpp"

class ClientException : public Exception
{
	private:
		int	_fd;

	public:
    	ClientException(const char *str, const std::string & ip, int fd) throw();
    	ClientException(ClientException const & src) throw();
    	~ClientException(void) throw();

		const char * what(void) const throw();
		int			getfd(void) const throw();

	private:
		ClientException(void) throw();
		ClientException &  operator=(ClientException const & src) throw();
};

#endif
