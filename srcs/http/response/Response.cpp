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
_payload(src._payload),
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
	_payload = src._payload;
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
Response::fill_body(std::string &str)
{
	_payload += str;
}

const std::string &
Response::send(void)
{
	if (!_header_sent)
	{
		set_resp_header(void);
		_header_sent = true;
	}
	_ready_to_send = false;
	return _payload;
}

void
Response::set_default_headers(void)
{
	_headers[SERVER_HEADER_INDEX].first = "Server";
	_headers[SERVER_HEADER_INDEX].second = "robin hoodie";
	_headers[DATE_HEADER_INDEX].first = "Date";
	_headers[LOCATION_HEADER_INDEX].first = "Location";
}

void
Response::set_date(void)
{
  char buf[1000]; //This buffer size should always be big enough to hold the date written by strftime
  time_t now = time(0);
  struct tm tm = *gmtime(&now);
  size_t len = strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
  _headers[DATE_HEADER_INDEX].second = std::string(buf, len);
}

void	
Response::add_header(const std::string & name, const std::string & value)
{
	_headers.push_back(header_t(name, value));
}

void
Response::reset(void)
{
	_payload.clear();
	_headers.clear();
	set_default_headers();
	_header_sent = false;
	_ready_to_send = false;
	_complete = false;
}

void
Response::set_resp_header(void)
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
	_payload.insert(0, h);
}

bool
Response::header_sent(void) const
{
	return _header_sent;
}
