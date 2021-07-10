#include "DeleteMethod.hpp"

DeleteMethod::DeleteMethod(void) {}

DeleteMethod::~DeleteMethod(void) {}

void
DeleteMethod::handle(void)
{}

bool
DeleteMethod::has_body(void)
{
	return false;
}

IHttpMethod *
DeleteMethod::create(void)
{
	return new DeleteMethod();
}
