#ifndef WEBSERV_CGIPARSER_HPP
# define WEBSERV_CGIPARSER_HPP

#include "CgiHeaderParser.hpp"
#include <vector>
#include <map>

class CgiParser {

	public:
		enum request_parsing_state {
			START,
			HEADERS,
			HEADER_NL,
			FINAL_NL,
			BODY
		};

	private:
		CgiHeaderParser			_header_parser;
		request_parsing_state	_request_state;
		std::vector<char>		_buffer;
		std::map<std::string, std::string>	_headers;

	public:
		CgiParser(void);
		~CgiParser(void);

		void	parse(void);
		void	setbuffer(char *buf, size_t len);

	private:
		CgiParser(CgiParser const & src);
		CgiParser &  operator=(CgiParser const & src);
		
		void    reset(void);
		void	parse_char(char c);
		void	add_header(void);
};

#endif
