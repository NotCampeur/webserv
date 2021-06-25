#ifndef REQUESTHEADERPARSER_H
# define REQUESTHEADERPARSER_H

# include "webserv.hpp"

class RequestHeaderParser
{
	private:
		typedef enum header_parsing_state {
			FIELD_NAME,
			COLON,
			FIELD_VALUE,
			TRAILING_WP,
			HEADER_CRLF
		};

		header_parsing_state	_state;
		std::string				_field_name;
		std::string				_field_value;

	public:

		RequestHeaderParser(void);
		RequestHeaderParser(RequestHeaderParser const & src);
		~RequestHeaderParser(void);

		RequestHeaderParser &  operator=(RequestHeaderParser const & src);

		bool	parse_char(char c) throw();
		void	reset(void);

	private:
		bool	RequestHeaderParser::iswhitespace(char c);
};
#endif
