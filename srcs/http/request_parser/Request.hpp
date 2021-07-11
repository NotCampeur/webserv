#ifndef WERSERV_REQUEST_H
# define WERSERV_REQUEST_H

# include "webserv.hpp"
# include "IHttpMethod.hpp"
# include "Exception.hpp"
# include "HttpException.hpp"

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

		void									set_method(IHttpMethod *method);
		IHttpMethod &							method(void);
		uri_t &									uri(void);
		std::map<std::string, std::string> &	headers(void);
		void									addbody(char *buf, size_t len);
		void									add_char_to_body(char c);
		const char *							get_body(void) const;
		size_t									bodysize(void) const;
		bool &									complete();
		void									reset(void);
		void									add_header(std::string & field_name, std::string & field_value);
};

#endif
