#include "DeleteMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

DeleteMethod::DeleteMethod(void) {}

DeleteMethod::~DeleteMethod(void) {}

// DeleteMethod::DeleteMethod(DeleteMethod const & src)
// {
// 	(void)src;
// }

// DeleteMethod &
// DeleteMethod::operator=(DeleteMethod const & src)
// {
// 	(void)src;
// 	return *this;
// }

void
DeleteMethod::handle(Request & req, Response & resp)
{
	int ret = remove((req.uri().path).c_str());

	if (ret != 0)
		throw SYSException("Remove operation failed");

	resp.set_http_code(StatusCodes::NO_CONTENT_204);
}

bool
DeleteMethod::has_body(void)
{
	return false;
}

// IHttpMethod *
// DeleteMethod::create_s(void)
// {
// 	return new DeleteMethod();
// }

// IHttpMethod *
// DeleteMethod::create_v(void)
// {
// 	return new DeleteMethod();
// }