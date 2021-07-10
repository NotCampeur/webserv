#include "PostMethod.hpp"

PostMethod::PostMethod(void) {}

PostMethod::~PostMethod(void) {}

void
PostMethod::handle(void)
{}

bool
PostMethod::has_body(void)
{
	return true;
}

IHttpMethod *
PostMethod::create(void)
{
	return new PostMethod();
}