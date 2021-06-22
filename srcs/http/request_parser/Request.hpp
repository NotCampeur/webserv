#ifndef WERSERV_REQUEST_H
# define WERSERV_REQUEST_H

# include "webserv.hpp"

class Request {

public:
    typedef enum http_method {
        GET,
        POST,
        DELETE
    };

    typedef struct uri
    {
        std::string path;
        std::string query;
        std::string fragment;
    };

    typedef std::vector<std::pair<std::string, std::string> > header_list;

    //Public for now to improve code readibility


private:
    http_method _method;
    uri         _uri;
    header_list _headers;
    bool        _complete;

public:

    Request(void);
    Request(Request const & src);
    ~Request(void);

    Request &  operator=(Request const & src);

    void    setmethod(http_method met);
    void    seturi(std::string & path, std::string & query, std::string & fragment);
    bool    iscomplete(void) const;

};

// std::ostream & operator<<(std::ostream & o, Request & req);

#endif
