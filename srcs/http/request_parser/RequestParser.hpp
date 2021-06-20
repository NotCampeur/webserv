#ifndef REQUESTPARSER_H
# define REQUESTPARSER_H

# include "webserv.hpp"
# include "Request.hpp"

class RequestParser {

private:
    const std::string & _request;
    std::string::iterator _offset;

public:

    RequestParser(void);
    RequestParser(std::string & request);

    RequestParser(RequestParser const & src);
    ~RequestParser(void);

    RequestParser &  operator=(RequestParser const & src);

    void    parse_request(void) const;

private:
    void    parse_method();
    void    parse_uri();

};

#endif
