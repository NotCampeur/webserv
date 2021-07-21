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
	set_content_length_header(req.uri().path.c_str(), resp);
	set_content_type_header(resp);
}

bool
HeadMethod::has_body(void)
{
	return false;
}

// IHttpMethod *
// HeadMethod::create_s(void)
// {
// 	return new HeadMethod();
// }

// IHttpMethod *
// HeadMethod::create_v(void)
// {
// 	return new HeadMethod();
// }

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
HeadMethod::set_content_type_header(Response & resp)
{
	const std::string path = resp.get_location();

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