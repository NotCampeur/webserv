#include "GetMethod.hpp"

GetMethod::GetMethod(void) {}

GetMethod::~GetMethod(void) {}

GetMethod::GetMethod(GetMethod const & src)
{
	(void)src;
}

GetMethod &
GetMethod::operator=(GetMethod const & src)
{
	(void)src;
	return *this;
}


void
GetMethod::handle(void)
{

}

bool
GetMethod::has_body(void)
{
	return false;
}

IHttpMethod *
GetMethod::create_s(void)
{
	return new GetMethod();
}

IHttpMethod *
GetMethod::create_v(void)
{
	return new GetMethod();
}