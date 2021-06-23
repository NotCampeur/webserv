#ifndef REQUESTPARSER_H
# define REQUESTPARSER_H

# include "webserv.hpp"
# include "Request.hpp"

class RequestParser {

public:
    typedef enum parsing_state {
        METHOD,
        URI,
        VERSION,
        HEADERS
    };

private:
    Request *               _request;
    
    std::string             _raw;
    std::string::iterator   _offset;
    parsing_state           _state;
    std::string             _httpmethod;
    std::string             _uri;

public:

    RequestParser(void);
    RequestParser(std::string & request);

    RequestParser(RequestParser const & src);
    ~RequestParser(void);

    RequestParser &  operator=(RequestParser const & src);

    void    reset(void);

    void    add_bytes_read(char *s, size_t len);
    void    parse(void);

private:
    void    parse_method();
    void    parse_uri();
    void    parse_query();
    void    check_version();
};

#endif
