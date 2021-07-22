#include "DeleteMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

DeleteMethod::DeleteMethod(void) {}

DeleteMethod::~DeleteMethod(void) {}

void
DeleteMethod::handle(Request & req, Response & resp)
{
	std::string path = req.uri().path;
	path.erase(path.begin()); // Remove leading '/'

	int ret = remove((path).c_str());

	if (ret != 0)
		throw SYSException("Remove operation failed");

	resp.set_http_code(StatusCodes::NO_CONTENT_204);
	resp.make_ready();
	resp.make_complete();
}

bool
DeleteMethod::has_body(void)
{
	return false;
}