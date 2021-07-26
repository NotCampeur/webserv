#include "HttpError.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

HttpError::HttpError(void) {}

HttpError::~HttpError(void) {}

void
HttpError::handle(Response & resp, StatusCodes::status_index_t error)
{
	int fd = open(resp.get_path().c_str(), O_RDONLY);
	if (fd < 0)
	{
		resp.set_error_default_msg(error);
	}

	resp.set_http_code(StatusCodes::NO_CONTENT_204);
	resp.ready_to_send() = true;
	resp.complete() = true;
}