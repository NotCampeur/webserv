#include "ReadHandler.hpp"
#include "InitiationDispatcher.hpp"

ReadHandler::ReadHandler(int fd, size_t file_size, Response & resp) :
_fd(fd),
_file_size(file_size),
_response(resp),
_event_flag(POLLIN),
_bytes_read(0)
{}

ReadHandler::ReadHandler(ReadHandler const & src) :
_fd(src._fd),
_file_size(src._file_size),
_response(src._response),
_event_flag(src._event_flag)
{}

ReadHandler::~ReadHandler(void)
{
	close(_fd);
}

void 
ReadHandler::readable(void)
{
	if (_response.iscomplete() || _response.ready_to_send())
		return ;

	char	read_buff[FILE_READ_BUF_SIZE];
	ssize_t len = read(_fd, read_buff, FILE_READ_BUF_SIZE);

	if (len < 0)
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Unable to read from file: ";//TBU << _response.get_location() << " : " << strerror(errno);
		manage_error();
	}
	else if (len == 0 )
	{
		if (_bytes_read == _file_size)
			response_complete();
		else
		{
			Logger(LOG_FILE, error_type, error_lvl) << "Read of size 0 from file: ";// TBU << _response.get_location();
			manage_error();
		}
	}
	else
	{
		_response.set_payload(std::string(read_buff, len));
		_bytes_read += static_cast<size_t>(len);
		std::cerr << "Total bytes read: " << _bytes_read << '\n';
		if (_bytes_read == _file_size)
			response_complete();
		else
			_response.make_ready();
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
	InitiationDispatcher::get_instance().remove_handle(_fd);
}

void
ReadHandler::response_complete(void)
{
	_response.make_ready();
	_response.make_complete();
	InitiationDispatcher::get_instance().remove_handle(_fd);
}