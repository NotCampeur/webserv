#include "Request.hpp"

Request::Request(void) {}

Request::Request(Request const & src)
{
    (void)src;
}

Request::~Request(void) {}

Request &
Request::operator=(Request const & src)
{
    return (*this);
}


void
Request::setmethod(http_method met)
{
    _method = met;
}

void
Request::seturi(std::string & path, std::string & query, std::string & fragment)
{
    _uri.path = path;
    _uri.query = query;
    _uri.fragment = fragment;
}