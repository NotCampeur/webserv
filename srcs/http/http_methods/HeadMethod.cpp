#include "HeadMethod.hpp"

HeadMethod::HeadMethod(void) {}

HeadMethod::~HeadMethod(void) {}

HeadMethod::HeadMethod(HeadMethod const & src)
{
	(void)src;
}

HeadMethod &
HeadMethod::operator=(HeadMethod const & src)
{
	(void)src;
	return *this;
}

void
HeadMethod::handle(void)
{}

bool
HeadMethod::has_body(void)
{
	return false;
}

IHttpMethod *
HeadMethod::create_s(void)
{
	return new HeadMethod();
}

IHttpMethod *
HeadMethod::create_v(void)
{
	return new HeadMethod();
}