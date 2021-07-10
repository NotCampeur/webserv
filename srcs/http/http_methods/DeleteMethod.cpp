#include "DeleteMethod.hpp"
#include <iostream>
DeleteMethod::DeleteMethod(void) {}

DeleteMethod::~DeleteMethod(void) {}

void
DeleteMethod::handle(void)
{
	std::cerr << "Handling Delete\n";
}

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
