#ifndef WEBSERV_SystemException_H
# define WEBSERV_SystemException_H

# include "webserv.hpp"

class SystemException : public std::exception
{
	protected:
		std::string			_msg;
		const int			_errno;

	public:
		explicit SystemException(const char *str) throw();
		SystemException(SystemException const & src) throw();
		~SystemException(void) throw();

		const char * what(void) const throw();

	private:
		SystemException(void) throw();
		SystemException &  operator=(SystemException const & src) throw();
};

#endif
