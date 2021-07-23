#include "GetMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

GetMethod::GetMethod(void) {}

GetMethod::~GetMethod(void) {}

/*
* FILE reader handle
* Needs: fd (open RDONLY)
* Buffer to read: for now reading in its own buffer, but potential optimization would see handler reading directly inside response buffer
* Destination
* access to set flag notifying there's something ready to be sent
* access to flag to check if the buffer is empty and can be filled
*/

void
GetMethod::handle(Request & req, Response & resp)
{
	std::string path = req.uri().path;
	path.erase(path.begin()); // Remove leading '/'

	resp.set_http_code(StatusCodes::OK_200);
	set_content_length_header(path, resp);
	set_content_type_header(path, resp);
	set_content_location_header(path, resp);
	std::cerr << "Request path: " << path << '\n';

	int fd = open(path.c_str(), O_RDONLY);
	if (fd < 0)
	{
		throw SYSException("Error opening file");
	}
	resp.set_handler_fd(fd);
	InitiationDispatcher::get_instance().add_read_handle(get_file_size(path), resp);
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

void
GetMethod::set_content_length_header(const std::string & path, Response & resp)
{
	off_t file_size = get_file_size(path);
	std::stringstream ss;
	ss << file_size;
	resp.add_header("Content-Length", ss.str());
}

off_t
GetMethod::get_file_size(const std::string & path)
{
	struct stat stat_buf;

	int ret = lstat(path.c_str(), &stat_buf);
	if (ret != 0)
	{
		throw SYSException("Error on lstat call");
	}

	return stat_buf.st_size;
}

//Sets content type header in response unless no file extansion is found or the file extansion is not defined in Mime (in these cases, the response does not have a Content-Type header)
void
GetMethod::set_content_type_header(const std::string & path, Response & resp)
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
GetMethod::set_content_location_header(const std::string & path, Response & resp)
{
	resp.add_header("Location", path);
}