#include "RequestParser.hpp"

RequestParser::RequestParser(std::string & request) :
_request(request),
_offset(request.begin())
{}

RequestParser::RequestParser(RequestParser const & src) :
_request(src._request),
_offset(src._offset)
{}

RequestParser::~RequestParser(void) {}

RequestParser &
RequestParser::operator=(RequestParser const & src)
{
    return (*this);
}

void
RequestParser::parse_request(void) const
{
    Request *req = new Request();
    
}

void
RequestParser::parse_method()
{
    
}

