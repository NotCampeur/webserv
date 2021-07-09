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

class RequestParser {

public:
    enum request_parsing_state {
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
	Request &							_request;
	RequestUriParser					_uri_parser;
	RequestHeaderParser					_header_parser;
	RequestBodyParser					_body_parser;

    request_parsing_state				_request_state;
	std::string							_buffer_leftovers;

	std::string  						_http_method;
	std::string							_http_version;

	size_t								_debug_code;

public:

    RequestParser(Request &req);
    // RequestParser(std::string & request);

    // RequestParser(RequestParser const & src);
    ~RequestParser(void);

    // RequestParser &  operator=(RequestParser const & src);

    void    parse(const char *buffer, size_t len);
	bool	iscomplete(void) const;
	void	next_request(void);

private:
	RequestParser(void);
    
	void    reset(void);
	void	parse_char(char c);
    void    parse_method(char c);
    void    check_version(char c);

	void	add_header(void);
};

#endif
