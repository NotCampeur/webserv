#ifndef WEBSERV_EXCEPTION_H
# define WEBSERV_EXCEPTION_H

# include "webserv.hpp"

class Exception : public std::exception
{
	protected:
		std::string	_msg;

	public:
    	Exception(const char *str) throw();
    	Exception(Exception const & src) throw();
    	~Exception(void) throw();

		Exception &  operator=(Exception const & src) throw();

		const char * what(void) const throw();

	private:
		Exception(void);
};

#endif
