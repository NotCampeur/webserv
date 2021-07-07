#include "HeadMethod.hpp"

HeadMethod::HeadMethod(void) {}

HeadMethod::~HeadMethod(void) {}

void
HeadMethod::handle(void)
{

}

bool
HeadMethod::has_body(void)
{
	return false;
}

IHttpMethod *
HeadMethod::create(void)
{
	return new HeadMethod();
}