#ifndef WEBSERV_EXCEPTION_H
# define WEBSERV_EXCEPTION_H

# include "webserv.hpp"

class Exception : std::exception
{
	private:
		std::string	_msg;

	public:

    	Exception(char *str);
    	Exception(Exception const & src);
    	~Exception(void);
		
		Exception &  operator=(Exception const & src);

		const char * what(void) const throw();

	private:
		Exception(void);
};

#endif
