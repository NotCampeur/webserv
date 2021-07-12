#include "DeleteMethod.hpp"

DeleteMethod::DeleteMethod(void) {}

DeleteMethod::~DeleteMethod(void) {}

DeleteMethod::DeleteMethod(DeleteMethod const & src)
{
	(void)src;
}

DeleteMethod &
DeleteMethod::operator=(DeleteMethod const & src)
{
	(void)src;
	return *this;
}

void
DeleteMethod::handle(void)
{}

bool
DeleteMethod::has_body(void)
{
	return false;
}

IHttpMethod *
DeleteMethod::create_s(void)
{
	return new DeleteMethod();
}

IHttpMethod *
DeleteMethod::create_v(void)
{
	return new DeleteMethod();
}