#ifndef WEBSERV_SYSEXCEPTION_H
# define WEBSERV_SYSEXCEPTION_H

# include "webserv.hpp"

class SYSException : std::exception
{
	private:
		std::string	_msg;
		int			_errno;

	public:

    	SYSException(char *str);
    	SYSException(SYSException const & src);
    	~SYSException(void);
		
		SYSException &  operator=(SYSException const & src);

		const char * what(void) const throw();

	private:
		SYSException(void);
};

#endif
