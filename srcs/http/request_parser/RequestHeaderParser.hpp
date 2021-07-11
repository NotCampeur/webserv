#ifndef WEBSERV_REQUESTHEADERPARSER_HPP
# define WEBSERV_REQUESTHEADERPARSER_HPP

# include "webserv.hpp"
# include "HttpException.hpp"

class RequestHeaderParser
{
	private:
		enum header_parsing_state {
			LEADING_WP,
			FIELD_NAME,
			COLON,
			FIELD_VALUE
		};

		header_parsing_state	_state;
		std::string				_field_name;
		std::string				_field_value;

	public:

		RequestHeaderParser(void);
		RequestHeaderParser(RequestHeaderParser const & src);
		~RequestHeaderParser(void);

		bool			parse_char(char c);
		void			reset(void);
		std::string	&	get_header_name(void);
		std::string	&	get_header_value(void);

	private:
		bool	iswhitespace(char c);
		void	remove_trailing_wp(std::string & s);
		void	addto_fieldname(char c);
		void	addto_fieldvalue(char c);
		RequestHeaderParser &  operator=(RequestHeaderParser const & src);
};
#endif
