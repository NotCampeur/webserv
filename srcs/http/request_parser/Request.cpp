#include "Request.hpp"

Request::Request(void) : _complete(false)
{}

Request::Request(Request const & src) :
_raw(src._raw),
_method(src._method),
_uri(src._uri),
_complete(src._complete)
{}

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
Request::add_bytes_read(char *s, size_t len)
{
    _raw += std::string(s, len);
}

void
Request::parse(void)
{
    
}

// std::ostream &
// operator<<(std::ostream & o, Request & req)
// {
//     o << "Request: \n" <<
// }