#include "DeleteMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

DeleteMethod::DeleteMethod(void) {}

DeleteMethod::~DeleteMethod(void) {}

void
DeleteMethod::handle(Request & req, Response & resp)
{
	if (resp.path_is_dir())
	{
		throw (HttpException(StatusCodes::FORBIDDEN_403));
	}

	int ret = remove(resp.get_path().c_str());

	if (ret != 0)
		throw SystemException("Remove operation failed");

	resp.set_http_code(StatusCodes::NO_CONTENT_204);
	resp.ready_to_send() = true;
	resp.complete() = true;

	(void)req;
}

bool
DeleteMethod::has_body(void)
{
	return false;
}