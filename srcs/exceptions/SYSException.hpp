#ifndef WEBSERV_SYSEXCEPTION_H
# define WEBSERV_SYSEXCEPTION_H

# include "webserv.hpp"

class SYSException : std::exception
{
	private:
		std::string	_msg;
		int			_errno;

	public:

    	SYSException(const char *str) throw();
    	SYSException(SYSException const & src) throw();
    	~SYSException(void) throw();
		
		SYSException &  operator=(SYSException const & src) throw();

		const char * what(void) const throw();

	private:
		SYSException(void) throw();
};

#endif
