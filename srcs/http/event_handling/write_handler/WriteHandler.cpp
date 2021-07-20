#include "WriteHandler.hpp"

WriteHandler::WriteHandler(int fd, const std::string & body, Response & resp) :
_fd(fd),
_body(body),
_response(resp),
_event_flag(POLLOUT)
{}

WriteHandler::WriteHandler(WriteHandler const & src) :
_fd(src._fd),
_body(src._body),
_response(src._response),
_event_flag(src._event_flag)
{}

WriteHandler::~WriteHandler(void)
{
	close(_fd);
}

void 
WriteHandler::readable(void)
{}

// Need to map file type and add header
void
WriteHandler::writable(void)
{

	set_content_type_header();

	ssize_t len;
	if (_bytes_written != 0 && _bytes_written != _body.size())
	{
		len = write(_fd, _body.substr(_bytes_written).c_str(), _body.size() - _bytes_written + 1);
	}
	else
	{
		len = write(_fd, _body.c_str(), _body.size());
	}
	
	if (len < 0)
	{
		manage_error();
	}
	else
	{
		_bytes_written += static_cast<size_t>(len); // Cast is safe as negative value would have been caught in above if statement

		if (_bytes_written == _body.size())
		{
			response_complete();
		}
	}
}

bool
WriteHandler::is_timeoutable(void) const
{
	return false;
}

bool
WriteHandler::is_timeout(void) const
{
	return false;
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

void
WriteHandler::set_content_type_header(void)
{
	const std::string path = _response.get_location();

	int i = path.size() - 1;
	for(; i >= 0; i--)
	{
		if (path[i] == '.')
			break;
	}
	if (i >= 0)
	{
		std::string file_ext = path.substr(i);
		_response.add_header("Content-Type", Mime::get_content_type(file_ext));
	}
	else
		_response.add_header("Content-Type", "text/plain"); // Same here, need to clarify
}