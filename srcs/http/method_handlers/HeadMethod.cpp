#include "HeadMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

HeadMethod::HeadMethod(void) {}

HeadMethod::~HeadMethod(void) {}

HeadMethod::HeadMethod(HeadMethod const & src)
{
	(void)src;
}

HeadMethod &
HeadMethod::operator=(HeadMethod const & src)
{
	(void)src;
	return *this;
}

void
HeadMethod::handle(Request & req, Response & resp)
{
	std::string path = req.uri().path;
	path.erase(path.begin());
	std::cerr << "Request path: " << path << '\n';

	set_content_length_header(path, resp);
	set_content_type_header(path, resp);
	set_content_location_header(path, resp);

	resp.set_http_code(StatusCodes::OK_200);
	resp.ready_to_send() = true;
	resp.complete() = true;
}

bool
HeadMethod::has_body(void)
{
	return false;
}

void
HeadMethod::set_content_length_header(const std::string & path, Response & resp)
{
	off_t file_size = get_file_size(path);
	std::stringstream ss;
	ss << file_size;
	resp.add_header("Content-Length", ss.str());
}

off_t
HeadMethod::get_file_size(const std::string & path)
{
	struct stat stat_buf;

	int ret = lstat(path.c_str(), &stat_buf);
	if (ret != 0)
	{
		throw SYSException("Error on lstat call");
	}

	return stat_buf.st_size;
}

void
HeadMethod::set_content_type_header(const std::string & path, Response & resp)
{
	int i = path.size() - 1;
	for(; i >= 0; i--)
	{
		if (path[i] == '.')
			break;
	}
	if (i >= 0)
	{
		std::string file_ext = path.substr(i);
		const std::string * mime_ext = Mime::get_content_type(file_ext);
		if (mime_ext != NULL)
			resp.add_header("Content-Type", *mime_ext);
	}
}

void
HeadMethod::set_content_location_header(const std::string & path, Response & resp)
{
	resp.add_header("Location", path);
}