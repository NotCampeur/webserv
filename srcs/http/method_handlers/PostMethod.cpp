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
PostMethod::handle(Request & req, Response & resp, InitiationDispatcher & idis)
{
	int fd = open(req.uri().path.c_str(), O_RDONLY);
	
	if (fd != 0)
	{
		throw SYSException("Error opening file");
	}

	idis.add_write_handle(fd, req.get_body(), resp);
}

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