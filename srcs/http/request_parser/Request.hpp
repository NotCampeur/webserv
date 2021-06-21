#ifndef WERSERV_REQUEST_H
# define WERSERV_REQUEST_H

# include "webserv.hpp"

class Request {

public:

    Request(void);
    Request(Request const & src);
    ~Request(void);

    Request &  operator=(Request const & src);

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

    void setmethod(http_method met);
    void seturi(std::string & path, std::string & query, std::string & fragment);

private:
    http_method _method;
    uri         _uri;
    bool        _complete;


};

#endif
