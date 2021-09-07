#ifndef WERSERV_REQUEST_H
# define WERSERV_REQUEST_H

# include "webserv.hpp"
# include "HttpException.hpp"
class IHttpMethod;
# include "IHttpMethod.hpp"
# include "RequestConfig.hpp"

class Request
{
	public:
		typedef std::map<std::string, const ServerConfig &> config_type;
		typedef std::vector<const std::string>				cookies_t;
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
		std::string							_body;
		const config_type &					_server_configs;
		RequestConfig *						_config;
		cookies_t							_cookies;

	public:
		Request(const config_type & server_configs);
		Request(Request const & src);
		~Request(void);

		void									set_method(IHttpMethod *method);
		IHttpMethod &							method(void);
		uri_t &									uri(void);
		std::map<std::string, std::string> &	headers(void);
		void									add_char_to_body(char c);
		const std::vector<char> &				get_body(void) const;
		size_t									bodysize(void) const;
		bool &									complete();
		void									reset(void);
		void									add_header(std::string & field_name, std::string & field_value);
		// const config_type &						server_configs(void) const;
		RequestConfig *							config(void) const;
		// Is called only one time after the headers have been parsed.
		void									load_request_config(void);
		const cookies_t &						get_cookies(void) const;


	private:
		const ServerConfig &					server_config(void) const;
		Request(void);
};

#endif
