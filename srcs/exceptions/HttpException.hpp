#ifndef WEBSERV_HTTPEXCEPTION_H
# define WEBSERV_HTTPEXCEPTION_H

# include "webserv.hpp"
# include "StatusCodes.hpp"

class HttpException
{
	private:
		StatusCodes::status_index_t _index;
		const std::string			_location;

	public:
    	HttpException(StatusCodes::status_index_t error) throw();
		HttpException(StatusCodes::status_index_t redir_code, const std::string & location) throw();
	    HttpException(HttpException const & src) throw();    	
		~HttpException(void) throw();

		StatusCodes::status_index_t	get_code_index(void) const throw();
		const std::string &			get_location(void) const throw();

	private:
		HttpException(void) throw();
		HttpException &  operator=(HttpException const & src) throw();
};

#endif