#ifndef WEBSERV_HTTPERROR_H
# define WEBSERV_HTTPERROR_H

# include "webserv.hpp"
# include "ClientSystemException.hpp"
# include "Singleton.hpp"
class Request;
class Response;

class HttpError : public Singleton<HttpError>
{
	public:
    	HttpError(void);
    	~HttpError(void);
		void	handle(Response & resp, StatusCodes::status_index_t error);

		private:
			HttpError(HttpError const & src);
			HttpError &  operator=(HttpError const & src);

};

#endif
