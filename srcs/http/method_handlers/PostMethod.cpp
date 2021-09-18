#include "PostMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

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

	if (!req.get_config()->upload_path().empty())
	{
		std::string upload_path = req.get_config()->upload_path();
		if (*upload_path.rbegin() != '/')
		{
			upload_path += '/';
		}

		for (size_t i = resp.get_path().size(); i > 0; --i)
		{
			if (resp.get_path()[i - 1] == '/' || i == 1)
			{
				upload_path += resp.get_path().substr(i);
				break ;
			}
		}
		std::cerr << "UPLOAD Path: " << upload_path << '\n';
		resp.set_path(upload_path);
	}

	resp.set_http_code(StatusCodes::CREATED_201);
	
	// set_content_location_header(resp);
	
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
		Logger(LOG_FILE, error_type, error_lvl) << "Pipe: " << std::strerror(errno);
		throw HttpException(StatusCodes::INTERNAL_SERVER_ERROR_500);
	}
	resp.set_handler_fd(pipe_fd[1]); // Setting handler to write end of the pipe, as CGI handler will first need to write to the pipe
	InitiationDispatcher::get_instance().add_cgi_handle(req, resp, pipe_fd, "POST");
}

// void
// PostMethod::set_content_location_header(const std::string & path, Response & resp)
// {
// 	resp.add_header("Location", path);
// }