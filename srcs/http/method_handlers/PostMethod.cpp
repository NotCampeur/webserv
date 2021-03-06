#include "PostMethod.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "InitiationDispatcher.hpp"
#include "Utils.hpp"
#include <fcntl.h>

#ifndef NAME_MAX
# define NAME_MAX 255 //usual C limit for filename
#endif

PostMethod::PostMethod(void) {}

PostMethod::~PostMethod(void) {}

void
PostMethod::handle(Request & req, Response & resp)
{
	if (resp.need_cgi())
	{
		add_cgi_handle(req, resp);
		return ;
	}

	if (resp.path_is_dir())
	{
		throw (HttpException(StatusCodes::FORBIDDEN_403));
	}

	std::string filename = Utils::get_filename_from_path(resp.get_path());
	if (filename.size() > NAME_MAX)
	{
		throw HttpException(StatusCodes::REQUEST_URI_TOO_LONG_414);
	}
	else if (!req.get_config()->upload_path().empty())
	{
		std::string upload_path = req.get_config()->upload_path();
		if (*upload_path.rbegin() != '/')
		{
			upload_path += '/';
		}
		upload_path += filename;
		resp.set_path(upload_path);
	}

	resp.set_http_code(StatusCodes::CREATED_201);
		
	int fd = open(resp.get_path().c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);

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

void
PostMethod::add_cgi_handle(Request & req, Response & resp)
{
	int pipe_fd[2];
	int ret = pipe(pipe_fd);
	if (ret < 0)
	{
		Logger(error_type, error_lvl) << "Pipe: " << std::strerror(errno);
		throw HttpException(StatusCodes::INTERNAL_SERVER_ERROR_500);
	}
	resp.set_handler_fd(pipe_fd[1]); // Setting handler to write end of the pipe, as CGI handler will first need to write to the pipe
	InitiationDispatcher::get_instance().add_cgi_handle(req, resp, pipe_fd, "POST");
}