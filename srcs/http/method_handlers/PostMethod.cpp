#include "PostMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

PostMethod::PostMethod(void) {}

PostMethod::~PostMethod(void) {}

// PostMethod::PostMethod(PostMethod const & src)
// {
// 	(void)src;
// }

// PostMethod &
// PostMethod::operator=(PostMethod const & src)
// {
// 	(void)src;
// 	return *this;
// }

void
PostMethod::handle(Request & req, Response & resp)
{
	int fd = open(req.uri().path.c_str(), O_RDONLY);
	
	if (fd != 0)
	{
		throw SYSException("Error opening file");
	}
	InitiationDispatcher::get_instance().add_write_handle(fd, req.get_body(), resp);
}

bool
PostMethod::has_body(void)
{
	return true;
}