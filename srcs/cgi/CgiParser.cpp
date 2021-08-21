#include "CgiParser.hpp"

CgiParser::CgiParser(void) {}

CgiParser::CgiParser(CgiParser const & src)
{
    (void)src;
}

CgiParser::~CgiParser(void) {}

CgiParser &
CgiParser::operator=(CgiParser const & src)
{
    return (*this);
}
