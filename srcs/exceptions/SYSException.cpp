#include "SYSException.hpp"

SYSException::SYSException(char *str, int error)
{}

SYSException::SYSException(SYSException const & src)
{
    (void)src;
}

SYSException::~SYSException(void) {}

SYSException &
SYSException::operator=(SYSException const & src)
{
    return (*this);
}
