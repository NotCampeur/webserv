#ifndef WEBSERV_ClientSystemException_H
# define WEBSERV_ClientSystemException_H

# include "webserv.hpp"
# include "SystemException.hpp"

class ClientSystemException : public SystemException
{
	private:
		int	_fd;

	public:
    	ClientSystemException(const char *str, const std::string & ip, int fd) throw();
    	ClientSystemException(ClientSystemException const & src) throw();
    	~ClientSystemException(void) throw();

		const char * what(void) const throw();
		int			getfd(void) const throw();

	private:
		ClientSystemException(void) throw();
		ClientSystemException &  operator=(ClientSystemException const & src) throw();
};

#endif
