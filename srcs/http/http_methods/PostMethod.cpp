#include "PostMethod.hpp"

PostMethod::PostMethod(void) {}

PostMethod::~PostMethod(void) {}

PostMethod::PostMethod(PostMethod const & src)
{
	(void)src;
}

PostMethod &
PostMethod::operator=(PostMethod const & src)
{
	(void)src;
	return *this;
}

void
PostMethod::handle(void)
{}

bool
PostMethod::has_body(void)
{
	return true;
}

IHttpMethod *
PostMethod::create_s(void)
{
	return new PostMethod();
}

IHttpMethod *
PostMethod::create_v(void)
{
	return new PostMethod();
}