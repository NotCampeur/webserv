#ifndef WEBSERV_REQUESTPARSER_HPP
# define WEBSERV_REQUESTPARSER_HPP

# include "webserv.hpp"
# include "Request.hpp"
# include "RequestUriParser.hpp"
# include "RequestHeaderParser.hpp"

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
		ERROR,
        DONE
    };

private:
	Request &							_request;
	RequestUriParser					_uri_parser;
	RequestHeaderParser					_header_parser;

    request_parsing_state				_request_state;
	std::string							_buffer_leftovers;
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
    void    request_error(int code);

	void	add_header(void);
};

#endif
