#ifndef WEBSERV_CLIENTSYSEXCEPTION_H
# define WEBSERV_CLIENTSYSEXCEPTION_H

# include "webserv.hpp"
# include "SYSException.hpp"

class ClientSYSException : public SYSException
{
	private:
		int	_fd;

	public:

    	ClientSYSException(const char *str, const std::string & ip, int fd) throw();
    	ClientSYSException(ClientSYSException const & src) throw();
    	~ClientSYSException(void) throw();

		const char * what(void) const throw();
		int			getfd(void) const throw();

	private:
		ClientSYSException(void) throw();
		ClientSYSException &  operator=(ClientSYSException const & src) throw();
};

#endif
