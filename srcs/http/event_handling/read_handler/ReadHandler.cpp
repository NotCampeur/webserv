#include "ReadHandler.hpp"
#include "InitiationDispatcher.hpp"

ReadHandler::ReadHandler(size_t file_size, Response & resp) :
_file_size(file_size),
_response(resp),
_event_flag(POLLIN),
_bytes_read(0)
{}

ReadHandler::ReadHandler(ReadHandler const & src) :
_file_size(src._file_size),
_response(src._response),
_event_flag(src._event_flag)
{}

ReadHandler::~ReadHandler(void)
{}

void 
ReadHandler::readable(void)
{
	if (_response.complete() || _response.ready_to_send())
		return ;

	char	read_buff[FILE_READ_BUF_SIZE];
	ssize_t len = read(_response.get_handler_fd(), read_buff, FILE_READ_BUF_SIZE);

	if (len < 0)
	{
		Logger(Arguments::get_instance().log_file(), error_type, error_lvl) << "Unable to read from file: " << _response.get_path() << " : " << strerror(errno);
		manage_error();
	}
	else if (len == 0 )
	{
		if (_bytes_read == _file_size)
			response_complete();
		else
		{
			Logger(Arguments::get_instance().log_file(), error_type, error_lvl) << "Read of size 0 from file: " << _response.get_path();
			manage_error();
		}
	}
	else
	{
		_response.set_payload(read_buff, len);
		_bytes_read += static_cast<size_t>(len);
		// std::cerr << "Total bytes read: " << _bytes_read << '\n';
		if (_bytes_read == _file_size)
			response_complete();
		else
			_response.ready_to_send() = true;
	}
}

void
ReadHandler::writable(void)
{}

bool
ReadHandler::is_timeoutable(void) const
{
	return false;
}

bool
ReadHandler::is_timeout(void) const
{
	return false;
}

int
ReadHandler::get_event_flag(void) const
{
	return _event_flag;
}

void
ReadHandler::manage_error(void)
{
	if (!_response.metadata_sent())
		_response.http_error(StatusCodes::INTERNAL_SERVER_ERROR_500);
}

void
ReadHandler::response_complete(void)
{
	_response.ready_to_send() = true;
	_response.complete() = true;
}