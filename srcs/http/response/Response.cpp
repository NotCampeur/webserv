#include "Response.hpp"
#include "InitiationDispatcher.hpp"
#include <sys/socket.h>
#include "Request.hpp"
// #define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

Response::Response(const Request & req) :
_version("HTTP/1.1"),
_metadata_sent(false),
_ready_to_send(false),
_complete(false),
_handler_fd(-1),
// _config(),
_req(req),
_error_manager(*this),
_path_is_dir(false),
_need_cgi(false),
_chunked(false)
{}

Response::Response(Response const & src) :
_payload(src._payload),
_ip(src._ip),
_version(src._version),
_headers(src._headers),
_metadata_sent(src._metadata_sent),
_ready_to_send(src._ready_to_send),
_complete(src._complete),
_handler_fd(src._handler_fd),
// _config(src._config),
_req(src._req),
_error_manager(src._error_manager),
_path_is_dir(src._path_is_dir),
_need_cgi(src._need_cgi),
_chunked(src._chunked)
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
	_path_is_dir = src._path_is_dir;
	_need_cgi = src._need_cgi;
	_chunked = src._chunked;
    return (*this);
}

// Response &
// Response::operator=(const RequestConfig & to_assign)
// {
// 	_config = to_assign;
//     return (*this);
// }

void
Response::set_http_code(StatusCodes::status_index_t i)
{
	_code = i;
}

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
Response::set_payload(const char *buf, size_t len)
{
	_payload.clear();
	if (_chunked)
	{
		insert_chunk_size(len);
		_payload.insert(_payload.end(), buf, buf + len);
		add_payload_crlf();
	}
	else
	{
		_payload.insert(_payload.begin(), buf, buf + len);
	}
}
// Return -1 if an error occured, 0 if some data was sent but tje entire payload content, 1 if the entire payload was sent successfully
int
Response::send_payload(int fd)
{
	// signal(SIGPIPE, SIG_IGN);
	if (!_metadata_sent)
	{
		set_resp_metadata();
		_metadata_sent = true;
	}
	if (_chunked && _complete)
	{
		add_last_chunk();
	}
	#ifdef MSG_NOSIGNAL
		ssize_t ret = send(fd, &_payload[0], _payload.size(), MSG_NOSIGNAL);
	#else
		signal(SIGPIPE, SIG_IGN);
		ssize_t ret = send(fd, &_payload[0], _payload.size(), 0);
	#endif

	if (ret < 0)
	{
		return -1;
	}
	if (static_cast<size_t>(ret) < _payload.size())
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Send() failed to send full buffer content: " <<  ret << " byte(s) sent instead of " << _payload.size();
		payload_erase(ret);
		return 0;
	}
	else
	{
		_payload.clear();
		_ready_to_send = false;
		return 1;
	}
	// std::cerr << "Resp content:\n" << std::string(&_payload[0], _payload.size()) << '\n';
	// return send_output;

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
	_payload.insert(_payload.begin(), meta.c_str(), meta.c_str() + meta.size());
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
	if (_chunked)
	{
		_headers.insert(_headers.begin(), header_t("Transfer-Encoding", "chunked"));
	}
	_headers.insert(_headers.begin(), header_t("Server", "robin hoodie"));
	_headers.insert(_headers.begin(), header_t("Date", ""));
	set_date(_headers.begin()->second);
}

void
Response::set_date(std::string & date)
{
  char buf[1000]; //This buffer size should always be big enough to hold the date written by strftime
  time_t now = time(0);
  struct tm tm;
  gmtime_r(&now, &tm);
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
	_path_is_dir = false;
	_need_cgi = false;
	_chunked = false;
	if (_handler_fd > 0)
	{
		InitiationDispatcher::get_instance().remove_handle(_handler_fd);
		close(_handler_fd);
		_handler_fd = 0;
	}
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
	std::vector<char>::iterator it = _payload.begin();
	_payload.erase(it, it + len);
}

const std::string &
Response::get_path(void) const
{
	return _file_path;
}

void
Response::set_path(const std::string & path)
{
	_file_path = path;
}

const RequestConfig &
Response::config(void) const
{
	return *_req.get_config();
}

void
Response::http_error(StatusCodes::status_index_t error)
{
	reset();
	_error_manager.handle(error);
}

bool &
Response::path_is_dir(void)
{
	return _path_is_dir;
}

bool &
Response::need_cgi(void)
{
	return _need_cgi;
}

void
Response::http_redirection(StatusCodes::status_index_t code, const std::string & location)
{
	reset();
	set_http_code(code);
	add_header("Content-Length", "0");
	std::string complete_location = "http://" + config().name() + ':' + config().port() + '/' + location;
	std::cerr << complete_location << '\n';
	add_header("Location", complete_location);
	ready_to_send() = true;
	complete() = true;
}

const std::string &
Response::get_ip(void)
{
	return _ip;
}

void
Response::send_chunks(void)
{
	_chunked = true;
}

void
Response::add_payload_crlf(void)
{
	_payload.push_back('\r');
	_payload.push_back('\n');
}

void
Response::insert_chunk_size(size_t len)
{
	if (len == 0)
	{		
		_payload.insert(_payload.begin(), '0');
	}
	else
	{
		size_t size = len;
		char hex[] = "0123456789ABCDEF";
		while (size != 0)
		{
			_payload.insert(_payload.begin(), hex[(size % 16)]);
			size /= 16;
		}
	}
	add_payload_crlf();
}

void
Response::add_last_chunk(void)
{
	_payload.push_back('0');
	add_payload_crlf();
	add_payload_crlf();
}