#ifndef WEBSERV_CGIPARSER_HPP
# define WEBSERV_CGIPARSER_HPP

#include "CgiHeaderParser.hpp"
#include <vector>
#include <map>
class Response;
#include "Response.hpp"

class CgiParser {

	public:
		typedef std::map<std::string, std::string> 					str_map;
		typedef std::vector<std::string>							cookies_t;

		enum request_parsing_state {
			HEADERS,
			BODY,
			DONE
		};

	private:
		Response &				_resp;
		CgiHeaderParser			_header_parser;
		request_parsing_state	_request_state;
		str_map					_headers;
		cookies_t				_cookies;

	public:
		CgiParser(Response & resp);
		~CgiParser(void);

		void	parse(char * buf, size_t len);

	private:
		CgiParser(void);
		CgiParser(CgiParser const & src);
		CgiParser &  operator=(CgiParser const & src);
		
		void    reset(void);
		void	parse_char(char c);
		void	add_header(void);
		
		// Return true if a body is expected
		void	set_resp_params(void);
		void	handle_cgi_redirect(long int error);
		void	add_all_cgi_headers(void);
};

#endif
