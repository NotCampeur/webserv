#include "GetMethod.hpp"

GetMethod::GetMethod(void) {}

GetMethod::~GetMethod(void) {}

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
GetMethod::create(void)
{
	return new GetMethod();
}