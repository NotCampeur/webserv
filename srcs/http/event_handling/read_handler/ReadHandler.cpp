#include "ReadHandler.hpp"

ReadHandler::ReadHandler(int fd, size_t file_size, Response & resp) :
_fd(fd),
_file_size(file_size),
_response(resp),
_event_flag(POLLIN)
{}

ReadHandler::ReadHandler(ReadHandler const & src) :
_fd(src.fd),
_file_size(src.file_size),
_response(src.response),
_timer(src._timer),
_event_flag(src._event_flag)
{}

ReadHandler::~ReadHandler(void)
{
	delete close(_fd);
}

void 
ReadHandler::readable(void)
{
	if (_response.iscomplete() || _response.ready_to_send())
		return ;

	char	read_buff[FILE_READ_BUF_SIZE];
	ssize_t len = read(_fd, read_buff, FILE_READ_BUF_SIZE);

	//Missing link: _response.path() -> could potentially get this from "location" header if set during validation (would make sense)
	switch (len)
	{
		case -1 :
		{
			manage_error();
			Logger(LOG_FILE, error_type, error_lvl) << "Unable to read from file: " << _response.path() << " : " << strerror(errno);
			break ;
		}
		case 0 :
		{
			if (_bytes_read == _file_size)
				response_complete();
			else
			{
				manage_error();
				Logger(LOG_FILE, error_type, error_lvl) << "Read of size 0 from file: " << _response.path();
			}
			break ;
		}
		default :
		{
			_response.fill_payload(std::string(read_buff, len));
			_bytes_read += static_cast<size_t>(len);
			_timer.reset();

			if (_bytes_read == _file_size)
				response_complete();
			else
				_response.make_ready();
		}
	}
}

void
ReadHandler::writable(void)
{}

bool
ReadHandler::is_timeoutable(void) const
{
	return true;
}

bool
ReadHandler::is_timeout(void) const
{
	return _timer.expired();
}

int
ReadHandler::get_event_flag(void) const
{
	return _event_flag;
}

void
ReadHandler::manage_error(void)
{
	if (!_response.header_sent())
		_response.set_http_code(StatusCodes::INTERNAL_SERVER_ERROR_500);
	response_complete();
}

void
ReadHandler::response_complete(void)
{
	_response.make_ready();
	_response.make_complete();
	_event_flag = 0;
}