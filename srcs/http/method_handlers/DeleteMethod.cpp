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
{
	int ret = remove(_path.c_str());

	if (ret != 0)
		throw SYSException("Remove operation failed");
}

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

void
DeleteMethod::set_path(const std::string & path)
{
	_path = path;
}