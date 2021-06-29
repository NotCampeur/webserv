#include "Request_delete.hpp"

Request::Request(void) : _complete(false)
{}

Request::Request(Request const & src) :
_method(src._method),
_uri(src._uri),
_headers(src._headers),
_complete(src._complete)
{}

Request::~Request(void) {}

// Request &
// Request::operator=(Request const & src)
// {
//     return (*this);
// }


void
Request::setmethod(http_method met)
{
    _method = met;
}

void
Request::seturi_path(std::string & path)
{
    _uri.path = path;
}

void
Request::seturi_query( std::string & query)
{
    _uri.query = query;
}

void
Request::seturi_fragment(std::string & fragment)
{
    _uri.fragment = fragment;
}


bool
Request::iscomplete(void) const
{
    return _complete;
}

void
Request::add_header(std::string & title, std::string & content)
{
    std::pair<std::string, std::string> * p = new std::pair<std::string, std::string>;
    p->first = title;
    p->second = content;

    _headers.push_back(*p);
}