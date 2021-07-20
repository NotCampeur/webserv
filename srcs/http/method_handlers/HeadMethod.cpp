#include "HeadMethod.hpp"

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
HeadMethod::handle(Request & req, Response & resp, InitiationDispatcher & idis)
{
	set_content_length_header(req.uri().path.c_str(), resp);
}

bool
HeadMethod::has_body(void)
{
	return false;
}

IHttpMethod *
HeadMethod::create_s(void)
{
	return new HeadMethod();
}

IHttpMethod *
HeadMethod::create_v(void)
{
	return new HeadMethod();
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