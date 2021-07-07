#ifndef WERSERV_REQUEST_H
# define WERSERV_REQUEST_H

# include "webserv.hpp"
# include "IHttpMethod.hpp"

class Request
{
	public:
		typedef struct	uri_s
		{
			std::string path;
			std::string query;
			std::string fragment;
		}				uri_t;

	private:
		bool								_complete;
		
		IHttpMethod *						_method;
		uri_t         						_uri;
		std::map<std::string, std::string>	_headers;
		char 								_body[MAX_CLIENT_BODY_SIZE];
		size_t								_body_size;

	public:

		Request(void);
		Request(Request const & src);
		~Request(void);

		IHttpMethod &							method(void);
		uri_t &									uri(void);
		std::map<std::string, std::string> &	headers(void);
		void									addbody(char *buf, size_t len);
		size_t									bodysize(void) const;
		bool &									complete();
		void									reset(void);
		void									add_header(std::string & field_name, std::string & field_value);

		// Exceptions

		class MaxBodySizeReached : public std::exception
		{
			const char * what() const throw();
		};
};

#endif
