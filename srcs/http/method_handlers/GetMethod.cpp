#include "GetMethod.hpp"

GetMethod::GetMethod(void) {}

GetMethod::~GetMethod(void) {}

GetMethod::GetMethod(GetMethod const & src)
{
	(void)src;
}

GetMethod &
GetMethod::operator=(GetMethod const & src)
{
	(void)src;
	return *this;
}


void
GetMethod::handle(Request & req, Response & resp)
{
	struct stat stat_buf;

	int ret = lstat(req.uri().path.c_str(), &stat_buf);
	if (ret != 0)
	{
		throw SYSException("Error on lstat call");
	}

	off_t file_size = stat_buf.st_size;
	std::stringstream ss;
	ss << file_size;
	resp.add_header("Content-Length", ss.str());

	int fd = open(req.uri().path.c_str(), O_RDONLY);
	if (fd != 0)
	{
		throw SYSException("Error on lstat call");
	}
	/*
		get file size 	-> set Content Length header
						-> set Content type header
		if is a directory:
			if index on:
				generate Index page
			if index off -> Should be handled at the validation level
		open file(path)
		new	read handler


	*/
}

bool
GetMethod::has_body(void)
{
	return false;
}

IHttpMethod *
GetMethod::create_s(void)
{
	return new GetMethod();
}

IHttpMethod *
GetMethod::create_v(void)
{
	return new GetMethod();
}