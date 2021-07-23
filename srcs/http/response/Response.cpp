#include "Response.hpp"
#include "InitiationDispatcher.hpp"

Response::Response(void) :
_version("HTTP/1.1"),
_metadata_sent(false),
_ready_to_send(false),
_complete(false),
_handler_fd(-1)
{}

Response::Response(Response const & src) :
_payload(src._payload),
_version(src._version),
_headers(src._headers),
_metadata_sent(src._metadata_sent),
_ready_to_send(src._ready_to_send),
_complete(src._complete),
_handler_fd(src._handler_fd)
{}

Response::~Response(void)
{
	if (_handler_fd > 0)
	{
		InitiationDispatcher::get_instance().remove_handle(_handler_fd);
		close(_handler_fd);
	}
}

Response &
Response::operator=(Response const & src)
{
	_payload = src._payload;
	_headers = src._headers;
	_metadata_sent = src._metadata_sent;
	_ready_to_send = src._ready_to_send;
	_complete = src._complete;
	_handler_fd = src._handler_fd;
    return (*this);
}

void
Response::set_http_code(StatusCodes::status_index_t i)
{
	_code = i;
}

// bool
// Response::ready_to_send(void) const
// {
// 	return _ready_to_send;
// }

bool &
Response::ready_to_send(void)
{
	return _ready_to_send;
}

bool &
Response::complete(void)
{
	return _complete;
}

void
Response::set_payload(const std::string & str)
{
	_payload = str;
}

const std::string &
Response::get_payload(void)
{
	if (!_metadata_sent)
	{
		set_resp_metadata();
		_metadata_sent = true;
	}
	return _payload;
}

bool
Response::metadata_sent(void) const
{
	return _metadata_sent;
}

void
Response::set_resp_metadata(void)
{
	std::string meta;
	set_status_line(meta);
	add_default_headers();
	
	for (size_t i = 0; i < _headers.size(); i++)
	{
		meta += _headers[i].first;
		meta += ": ";
		meta += _headers[i].second;
		meta += "\r\n";
	}
	meta += "\r\n";
	_payload.insert(0, meta);
}

void
Response::set_status_line(std::string & meta)
{
	meta += _version;
	meta += ' ';
	meta += StatusCodes::get_code_msg_from_index(_code);
	meta += "\r\n";
}

void
Response::add_default_headers(void)
{
	_headers.insert(_headers.begin(), header_t("Server", "robin hoodie"));
	_headers.insert(_headers.begin(), header_t("Date", ""));
	set_date(_headers.begin()->second);
}

void
Response::set_date(std::string & date)
{
  char buf[1000]; //This buffer size should always be big enough to hold the date written by strftime
  time_t now = time(0);
  struct tm tm = *gmtime(&now);
  size_t len = strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
  date = std::string(buf, len);
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
	_metadata_sent = false;
	_ready_to_send = false;
	_complete = false;
	if (_handler_fd > 0)
	{
		InitiationDispatcher::get_instance().remove_handle(_handler_fd);
		close(_handler_fd);
		_handler_fd = 0;
	}
}

const std::string &
Response::get_location(void)
{
	return _headers[LOCATION_HEADER_INDEX].second;
}

void
Response::http_error(StatusCodes::status_index_t error)
{
	// Check if error code has an error page setup in config file
	_ready_to_send = true;
	_complete = true;
	set_http_code(error);

	static std::string err_msg_part_1("<html>\n<head><title>");
	static std::string err_msg_part_2("</title></head>\n<body bgcolor=\"white\">\n<center><h1>");
	static std::string err_msg_part_3("</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>");
	
	std::string full_msg = err_msg_part_1 + StatusCodes::get_code_msg_from_index(_code) + err_msg_part_2 + StatusCodes::get_code_msg_from_index(_code) + err_msg_part_3;

	std::stringstream ss;
	ss << full_msg.size();
	_headers.clear(); // Remove any header that may have been set while processing the request before an error occured
	add_header("Content-Length", ss.str().c_str());
	add_header("Content-Type", "text/html");
	set_payload(full_msg);
}

void
Response::set_handler_fd(int fd)
{
	_handler_fd = fd;
}

int
Response::get_handler_fd(void) const
{
	return _handler_fd;
}

void
Response::payload_erase(size_t len)
{
	_payload.erase(0, len);
}