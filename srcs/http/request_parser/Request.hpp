#ifndef WERSERV_REQUEST_H
# define WERSERV_REQUEST_H

# include "webserv.hpp"

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
		
		std::string  						_http_method;
		std::string							_http_version;
		uri_t         						_uri;
		std::map<std::string, std::string>	_headers;

	public:

		Request(void);
		Request(Request const & src);
		~Request(void);

		std::string &							method(void);
		uri_t &									uri(void);
		std::string &							version(void);
		std::map<std::string, std::string> &	headers(void);
		bool &									complete();
		void									reset(void);
		void									add_header(std::string & field_name, std::string & field_value);
};

#endif
