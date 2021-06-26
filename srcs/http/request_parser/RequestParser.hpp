#ifndef WEBSERV_REQUESTPARSER_HPP
# define WEBSERV_REQUESTPARSER_HPP

# include "webserv.hpp"
# include "Request.hpp"
# include "RequestUriParser.hpp"
# include "RequestHeaderParser.hpp"

class RequestParser {

public:
    enum request_parsing_state {
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
	RequestUriParser					_uri_parser;
	RequestHeaderParser					_header_parser;

	bool								_complete;
    request_parsing_state				_request_state;
    std::string  						_http_method;
	std::string							_http_version;
	std::map<std::string, std::string>	_headers;

	std::string							_buffer_leftovers;

	size_t								_debug_code;

public:

    RequestParser(void);
    // RequestParser(std::string & request);

    // RequestParser(RequestParser const & src);
    ~RequestParser(void);

    // RequestParser &  operator=(RequestParser const & src);

    void    parse(const char *buffer, size_t len);
	bool	iscomplete(void) const;
	void	next_request(void);

private:
    void    reset(void);

	void	parse_char(char c);
    void    parse_method(char c);
    void    check_version(char c);
    void    request_error(int code);

	void	add_header(void);
};

#endif
