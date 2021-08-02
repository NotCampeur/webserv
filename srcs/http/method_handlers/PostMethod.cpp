#include "PostMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

PostMethod::PostMethod(void) {}

PostMethod::~PostMethod(void) {}

void
PostMethod::handle(Request & req, Response & resp)
{
	if (resp.path_is_dir())
	{
		throw (HttpException(StatusCodes::FORBIDDEN_403));
	}
	resp.set_http_code(StatusCodes::CREATED_201);
	
	// set_content_location_header(resp);
	
	int fd = open(resp.get_path().c_str(), O_WRONLY | O_CREAT, 0666);

	if (fd < 0)
	{
		throw SystemException("Error opening file");
	}
	resp.set_handler_fd(fd);
	InitiationDispatcher::get_instance().add_write_handle(req.get_body(), resp);
}

bool
PostMethod::has_body(void)
{
	return true;
}

// void
// PostMethod::set_content_location_header(const std::string & path, Response & resp)
// {
// 	resp.add_header("Location", path);
// }