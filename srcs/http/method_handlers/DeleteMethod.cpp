#include "DeleteMethod.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "InitiationDispatcher.hpp"

DeleteMethod::DeleteMethod(void) {}

DeleteMethod::~DeleteMethod(void) {}

void
DeleteMethod::handle(Request & req, Response & resp)
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

	int ret = remove(resp.get_path().c_str());

	if (ret != 0)
		throw SystemException("Remove operation failed");

	resp.set_http_code(StatusCodes::NO_CONTENT_204);
	resp.ready_to_send() = true;
	resp.complete() = true;

	(void)req;
}

bool
DeleteMethod::has_body(void)
{
	return false;
}

void
DeleteMethod::add_cgi_handle(Request & req, Response & resp)
{
	int pipe_fd[2];
	int ret = pipe(pipe_fd);
	if (ret < 0)
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Pipe: " << std::strerror(errno);
		throw HttpException(StatusCodes::INTERNAL_SERVER_ERROR_500);
	}
	resp.set_handler_fd(pipe_fd[1]); // Setting handler to write end of the pipe, as CGI handler will first need to write to the pipe
	InitiationDispatcher::get_instance().add_cgi_handle(req, resp, pipe_fd, "DELETE");
}