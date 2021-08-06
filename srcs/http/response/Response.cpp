#include "Response.hpp"
#include "InitiationDispatcher.hpp"

Response::Response(const ServerConfig & config) :
_version("HTTP/1.1"),
_metadata_sent(false),
_ready_to_send(false),
_complete(false),
_handler_fd(-1),
_server_config(config),
_error_manager(_server_config, *this),
_path_is_dir(false)
{}

Response::Response(Response const & src) :
_payload(src._payload),
_version(src._version),
_headers(src._headers),
_metadata_sent(src._metadata_sent),
_ready_to_send(src._ready_to_send),
_complete(src._complete),
_handler_fd(src._handler_fd),
_server_config(src._server_config),
_error_manager(src._error_manager),
_path_is_dir(src._path_is_dir)
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
    return (*this);
}

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
	_path_is_dir = false;
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
	_payload.erase(0, len);
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

const ServerConfig &
Response::get_server_config(void) const
{
	return _server_config;
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

void
Response::http_redirection(StatusCodes::status_index_t code, const std::string & location)
{
	reset();
	set_http_code(code);
	add_header("Content-Length", "0");
	std::string complete_location = "http://" + _server_config.name() + ':' + _server_config.port() + '/' + location;
	std::cerr << complete_location << '\n';
	add_header("Location", complete_location);
	ready_to_send() = true;
	complete() = true;
}