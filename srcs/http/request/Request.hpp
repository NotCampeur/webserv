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
		RequestConfig *						_config;

	public:
		Request(const config_type & server_configs);
		Request(Request const & src);
		~Request(void);

		void									set_method(IHttpMethod *method);
		IHttpMethod &							method(void);
		uri_t &									uri(void);
		std::map<std::string, std::string> &	headers(void);
		void									add_char_to_body(char c);
		const std::string &						get_body(void) const;
		size_t									bodysize(void) const;
		bool &									complete();
		void									reset(void);
		void									add_header(std::string & field_name, std::string & field_value);
		RequestConfig *							config(void) const;
		void									set_config(RequestConfig * config);

	private:
		Request(void);
};

#endif
