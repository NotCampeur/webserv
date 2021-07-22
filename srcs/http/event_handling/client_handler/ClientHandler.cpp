#include "ClientHandler.hpp"

ClientHandler::ClientHandler(const Client & client) :
_client(client),
_request(),
_req_parser(_request),
_timer(CLIENT_TIMEOUT),
_event_flag(POLLIN)
{}

ClientHandler::ClientHandler(ClientHandler const & src) :
_client(src._client),
_request(src._request),
_req_parser(src._req_parser),
_timer(src._timer),
_event_flag(src._event_flag)
{}

ClientHandler::~ClientHandler(void)
{
	delete &_client;
}

int
ClientHandler::get_clientfd(void) const
{
	return _client.getsockfd();
}

void 
ClientHandler::readable(void)
{
	char		read_buff[RECV_BUF_SIZE] = {0};
	ssize_t		bytes_read;

	bytes_read = recv(_client.getsockfd(), read_buff, RECV_BUF_SIZE, 0);

	switch (bytes_read)
	{
		case -1 :
		{
			throw ClientSYSException("Unable to read from client socket", _client.getip(), _client.getsockfd());
		}
		case 0 :
		{
			throw ClientException("Connection closed by client", _client.getip(), _client.getsockfd());
		}
		default :
		{
			_req_parser.setbuffer(read_buff, bytes_read);
			handle_request();
		}
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "Socket content (" << bytes_read << " byte read): " << read_buff;
}

void
ClientHandler::writable(void)
{
	if (_response.ready_to_send())
	{
		ssize_t	bytes_written = send(get_clientfd(), _response.get_payload().c_str(), _response.get_payload().size(), 0);
		std::cerr << _response.get_payload();
		if (bytes_written < 0)
		{
			throw ClientSYSException("Unable to write to client socket", _client.getip(), _client.getsockfd());
		}
		else if (static_cast<size_t>(bytes_written) != _response.get_payload().size()) // Static cast is safe here as a negative value would have been caught by prior if statement, then, a positive ssize_t will always fit in a size_t
		{
			throw ClientException("Could not write entire buffer content to socket", _client.getip(), _client.getsockfd()); // This Should eventually be handled properly
		}
		Logger(LOG_FILE, basic_type, minor_lvl) << "Message written to client socket: " << get_clientfd() << " : " << _response.get_payload();
		if (_response.iscomplete())
		{
			_response.reset();
			_req_parser.next_request();
			if (!_request.complete())
				_event_flag = POLLIN;
		}
	}
}

bool
ClientHandler::is_timeoutable(void) const
{
	return true;
}

bool
ClientHandler::is_timeout(void) const
{
	return _timer.expired();
}

int
ClientHandler::get_event_flag(void) const
{
	return _event_flag;
}

void
ClientHandler::handle_request(void)
{
	// Could have a try/catch here catching HttpExceptions and have a routine to handle them
	
	try {
		parse_request();
		if (_request.complete())
			// validate();
		// if (_request.validated())
			_request.method().handle(_request, _response);
	}
	catch (HttpException & e)
	{
		Logger(LOG_FILE, basic_type, major_lvl) << "Http Exception: " << StatusCodes::get_code_msg_from_index(e.get_error_index());
		handle_http_error(e.get_error_index());
	}
	catch (SYSException & e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what() << " : " << _client.getip();
		handle_http_error(StatusCodes::INTERNAL_SERVER_ERROR_500);
	}
}

void	
ClientHandler::parse_request(void)
{
	_req_parser.parse();
	if (_request.complete())
		_event_flag = POLLOUT;
}

void
ClientHandler::handle_http_error(StatusCodes::status_index_t error_code)
{
	_request.complete() = true;
	_response.http_error(error_code);
	_response.make_ready();
	_response.make_complete();
	_event_flag = POLLOUT;	
}
/*
void
ClientHandler::set_header(std::stringstream & header, size_t content_length)
{	
	header << "HTTP/1.1 200 OK\r\n"
	<< "Content-Type: text\r\n"
	<< "Content-Length: "
	<< (content_length)
	<< "\r\n\r\n";
}
*/