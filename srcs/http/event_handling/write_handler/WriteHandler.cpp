#include "WriteHandler.hpp"

WriteHandler::WriteHandler(int fd, const std::string & body, Response & resp) :
_fd(fd),
_body(body),
_response(_resp),
_timer(FILE_HANDLER_TIMEOUT),
_event_flag(POLLOUT)
{}

WriteHandler::WriteHandler(WriteHandler const & src) :
_fd(src._fd),
_body(src._body),
_response(src._response),
_timer(src._timer),
_event_flag(src._event_flag)
{}

WriteHandler::~WriteHandler(void)
{
	close(_fd);
}

void 
WriteHandler::readable(void)
{}

void
WriteHandler::writable(void)
{
	ssize_t len;
	if (_bytes_written != 0 && _bytes_written != body.size())
	{
		len = write(_fd, body.substr(_bytes_written).c_str(), body.size() - _bytes_written + 1);
	}
	else
	{
		len = write(_fd, body.c_str(), body.size());
	}
	
	if (len < 0)
	{
		manage_error();
	}
	
	_bytes_written += static_cast<size_t>(len);
	
	if (_bytes_written == body.size())
	{
		response_complete();
	}
}

bool
WriteHandler::is_timeoutable(void) const
{
	return true;
}

bool
WriteHandler::is_timeout(void) const
{
	return _timer.expired();
}

int
WriteHandler::get_event_flag(void) const
{
	return _event_flag;
}

void
WriteHandler::response_complete(void)
{
	_response.make_ready();
	_response.make_complete();
	_event_flag = 0;
}

void
WriteHandler::manage_error(void)
{
	if (!_response.header_sent())
		_response.set_http_code(StatusCodes::INTERNAL_SERVER_ERROR_500);
	response_complete();
}