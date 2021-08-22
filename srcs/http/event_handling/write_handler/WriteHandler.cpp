#include "WriteHandler.hpp"
#include "InitiationDispatcher.hpp"

WriteHandler::WriteHandler(const std::vector<char> & body, Response & resp) :
_body(body),
_response(resp),
_event_flag(POLLOUT),
_bytes_written(0)
{}

WriteHandler::WriteHandler(WriteHandler const & src) :
_body(src._body),
_response(src._response),
_event_flag(src._event_flag),
_bytes_written(src._bytes_written)
{}

WriteHandler::~WriteHandler(void)
{}

void 
WriteHandler::readable(void)
{}

// Need to map file type and add header
void
WriteHandler::writable(void)
{
	ssize_t len;
	if (_bytes_written != 0 && _bytes_written != _body.size()) // Something has already been written to the file, but not the full body content
	{
		len = write(_response.get_handler_fd(), &_body[_bytes_written], _body.size() - _bytes_written); //Removed the +1
		
		if (len < 0)
		{
			manage_error();
		}
		else
		{
			_bytes_written += static_cast<size_t>(len); // Cast is safe as negative value would have been caught in above if statement
			std::cerr << "Body size: " << _body.size() << " ; Bytes written: " << _bytes_written << '\n';
			if (_bytes_written == _body.size())
			{
				response_complete();
			}
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
	_response.ready_to_send() = true;
	_response.complete() = true;
}

void
WriteHandler::manage_error(void)
{
	if (!_response.metadata_sent())
		_response.http_error(StatusCodes::INTERNAL_SERVER_ERROR_500);
	response_complete();
}