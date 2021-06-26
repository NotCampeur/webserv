#ifndef WEBSERV_REQUESTHEADERPARSER_HPP
# define WEBSERV_REQUESTHEADERPARSER_HPP

# include "webserv.hpp"

class RequestHeaderParser
{
	private:
		enum header_parsing_state {
			FIELD_NAME,
			COLON,
			FIELD_VALUE
		};

		header_parsing_state	_state;
		std::string				_field_name;
		std::string				_field_value;

	public:

		RequestHeaderParser(void);
		// RequestHeaderParser(RequestHeaderParser const & src);
		~RequestHeaderParser(void);

		// RequestHeaderParser &  operator=(RequestHeaderParser const & src);

		bool		parse_char(char c);
		void		reset(void);
		std::string	get_header_name(void) const;
		std::string	get_header_value(void) const;

	private:
		bool	iswhitespace(char c);
};
#endif
