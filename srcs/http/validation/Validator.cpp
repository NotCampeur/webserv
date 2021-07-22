#include "Validator.hpp"

Validator::Validator(void) {}

Validator::Validator(Validator const & src)
{
    (void)src;
}

Validator::~Validator(void) {}

Validator &
Validator::operator=(Validator const & src)
{
    return (*this);
}
