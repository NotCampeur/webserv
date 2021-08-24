#ifndef WEBSERV_REQUESTPARSER_HPP
# define WEBSERV_REQUESTPARSER_HPP

# include "webserv.hpp"
# include "Request.hpp"
# include "RequestUriParser.hpp"
# include "RequestHeaderParser.hpp"
# include "RequestBodyParser.hpp"
# include "DeleteMethod.hpp"
# include "GetMethod.hpp"
# include "HeadMethod.hpp"
# include "PostMethod.hpp"
# include "HttpException.hpp"

class RequestParser
{
	public:
		enum request_parsing_state
		{
			START,
			METHOD,
			URI,
			VERSION,
			REQ_LINE_CRLF,
			HEADERS,
			HEADER_CRLF,
			FINAL_CRLF,
			BODY,
			DONE
		};

	private:
		Request &					_request;
		RequestUriParser			_uri_parser;
		RequestHeaderParser			_header_parser;
		RequestBodyParser			_body_parser;

		request_parsing_state		_request_state;
		std::string					_buffer;
		std::string					_buffer_leftovers;

		std::string  				_http_method;
		std::string					_http_version;

	public:
		RequestParser(Request &req);

		RequestParser(RequestParser const & src);
		~RequestParser(void);

		void	setbuffer(char *buf, size_t len);
		void	setbuffer(std::string & str);
		void    parse(void);
		//Clear content of current request, if there were any buffer leftovers from the previous request, they are set into the main buffer, so a subsequent call to 'parse()' would parse the content
		void	next_request(void);

	private:
		RequestParser(void);
		RequestParser &  operator=(RequestParser const & src);
		
		void    reset(void);
		void	parse_char(char c);
		void    parse_method(char c);
		void    check_version(char c);
		bool	correct_version_format(void);
		void	add_header(void);
};

#endif
