#ifndef REQUESTPARSER_H
# define REQUESTPARSER_H

# include "webserv.hpp"
# include "Request.hpp"
# include "RequestUriParser.hpp"
# include "RequestHeaderParser.hpp"

class RequestParser {

public:
    typedef enum request_parsing_state {
        METHOD,
        URI,
        VERSION,
		REQ_LINE_CRLF,
        HEADERS,
		HEADER_CRLF,
		FINAL_CRLF,
        DONE
    };

private:
    Request *               _request;
	RequestUriParser		_uri_parser;
	RequestHeaderParser		_header_parser;

    std::string  			_buffer;
    size_t       			_offset;
    request_parsing_state	_request_state;
    std::string  			_http_method;
	std::string				_http_version;

public:

    RequestParser(void);
    RequestParser(std::string & request);

    RequestParser(RequestParser const & src);
    ~RequestParser(void);

    RequestParser &  operator=(RequestParser const & src);

    void    add_bytes_read(char *s, size_t len);
    void    parse(void);

private:
    void    reset(void);

    void    parse_method(char c);
    void    check_version(char c);
    void    request_error(int code);
};

#endif
