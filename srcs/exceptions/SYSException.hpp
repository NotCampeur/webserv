#ifndef WEBSERV_SYSEXCEPTION_H
# define WEBSERV_SYSEXCEPTION_H

# include "webserv.hpp"

class SYSException : std::exception
{
	protected:
		std::string			_msg;
		const int			_errno;

	public:

    	explicit SYSException(const char *str) throw();
    	SYSException(SYSException const & src) throw();
    	~SYSException(void) throw();
		

		const char * what(void) const throw();

	private:
		SYSException(void) throw();
		SYSException &  operator=(SYSException const & src) throw();
};

#endif
