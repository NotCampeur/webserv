#include "Response.hpp"

Response::Response(void) :
_version("HTTP/1.1"),
_headers(DEFAULT_HEADERS_COUNT),
_header_sent(false),
_ready_to_send(false),
_complete(false)
{
	set_default_headers();
}

Response::Response(Response const & src) :
_buffer(src._buffer),
_version(src._version),
_headers(src._headers),
_header_sent(src._header_sent),
_ready_to_send(src._ready_to_send),
_complete(src._complete)
{}

Response::~Response(void) {}

Response &
Response::operator=(Response const & src)
{
	_buffer = src._buffer;
	_headers = src._headers;
	_header_sent = src._header_sent;
	_ready_to_send = src._ready_to_send;
	_complete = src._complete;
    return (*this);
}

void
Response::set_http_code(StatusCodes::status_index_t i)
{
	_code = i;
}

bool
Response::ready_to_send(void) const
{
	return _ready_to_send;
}

void
Response::make_ready(void)
{
	_ready_to_send = true;
}

bool
Response::iscomplete(void) const
{
	return _complete;
}

void
Response::make_complete(void)
{
	_complete = true;
}

void
Response::fill_response(std::string &str)
{
	_buffer += str;
}

const std::string &
Response::send(void)
{
	if (!_header_sent)
	{
		std::string h(_version);
		h += ' ';
		h += StatusCodes::get_error_msg_from_index(_code);
		h += "\r\n";
		this->set_date();
		for (size_t i = 0; i < _headers.size(); i++)
		{
			h += _headers[i].first;
			h += ": ";
			h += _headers[i].second;
			h += "\r\n";
		}
		h += "\r\n";
		_buffer.insert(0, h);
		_header_sent = true;
	}
	_ready_to_send = false;
	return _buffer;
}

void
Response::set_default_headers(void)
{
	_headers[SERVER_HEADER_INDEX].first = "Server";
	_headers[SERVER_HEADER_INDEX].second = "robin hood";
	_headers[DATE_HEADER_INDEX].first = "Date";
	_headers[LOCATION_HEADER_INDEX].first = "Location";
}

void
Response::set_date(void)
{
  char buf[1000];
  time_t now = time(0);
  struct tm tm = *gmtime(&now);
  size_t len = strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
  _headers[DATE_HEADER_INDEX].second = std::string(buf, len);
}

void
Response::reset(void)
{
	_buffer.clear();
	_headers.clear();
	set_default_headers();
	_header_sent = false;
	_ready_to_send = false;
	_complete = false;
}