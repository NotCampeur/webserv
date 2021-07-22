#include "PostMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

PostMethod::PostMethod(void) {}

PostMethod::~PostMethod(void) {}

void
PostMethod::handle(Request & req, Response & resp)
{
	std::string path = req.uri().path;
	path.erase(path.begin()); // Remove starting '/'
	std::cerr << "Request path: " << path << '\n';
	set_content_location_header(path, resp);
	resp.set_http_code(StatusCodes::CREATED_201);

	int fd = open(path.c_str(), O_RDONLY | O_CREAT);
	
	if (fd < 0)
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

void
PostMethod::set_content_location_header(const std::string & path, Response & resp)
{
	resp.add_header("Location", path);
}