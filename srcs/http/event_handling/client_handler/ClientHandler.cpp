#include "ClientHandler.hpp"
#include "Validator.hpp"

ClientHandler::ClientHandler(const Client & client) :
_client(client),
_request(client.get_server_config()),
_response(client.get_server_config(), client.getip()),
_req_parser(_request),
_timer(CLIENT_TIMEOUT),
_event_flag(POLLIN)
{}

ClientHandler::ClientHandler(ClientHandler const & src) :
_client(src._client),
_request(src._request),
_response(src._response),
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
			throw ClientSystemException("Unable to read from client socket", _client.getip(), _client.getsockfd());
		}
		case 0 :
		{
			throw ClientException("Connection closed by client", _client.getip(), _client.getsockfd());
		}
		default :
		{
			_req_parser.setbuffer(read_buff, bytes_read);
			handle_request();
			_timer.reset();
		}
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "Socket content (" << bytes_read << " byte read): " << read_buff;
}

void
ClientHandler::writable(void)
{
	if (_response.ready_to_send())
	{
		std::pair<ssize_t, ssize_t> output = _response.send_payload(_client.getsockfd());
		if (output.first < 0)
		{
			throw ClientSystemException("Unable to write to client socket", _client.getip(), _client.getsockfd());
		}
		else if (static_cast<size_t>(output.first) < output.second) // Static cast is safe here as a negative value would have been caught by prior if statement, then, a positive ssize_t will always fit in a size_t
		{
			_response.payload_erase(static_cast<size_t>(output.first));
			_timer.reset();
			Logger(LOG_FILE, basic_type, minor_lvl) << "Could not write entire buffer content to socket: " << _client.getip() << " : " << _client.getsockfd();

			// throw ClientException("Could not write entire buffer content to socket", _client.getip(), _client.getsockfd()); // This Should eventually be handled properly
		}
		else
		{
			_timer.reset();
			_response.ready_to_send() = false;
			if (_response.complete())
			{
				_response.reset();
				_req_parser.next_request();
				if (!_request.complete())
					_event_flag = POLLIN;
			}
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
	try {
		parse_request();
		if (_request.complete())
		{
			Validator::get_instance().validate_request_inputs(_request, _response);
			_request.method().handle(_request, _response);
		}
	}
	catch (HttpException & e)
	{
		Logger(LOG_FILE, basic_type, major_lvl) << "Http Exception: " << StatusCodes::get_code_msg_from_index(e.get_code_index());
		
		if (StatusCodes::get_code_value(e.get_code_index()) >= 400)
		{
			handle_http_error(e.get_code_index());
		}
		else
		{
			std::cerr << "Redir caught\n";
			_response.http_redirection(e.get_code_index(), e.get_location());
		}
	}
	catch (SystemException & e)
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
	_response.http_error(error_code);
	_event_flag = POLLOUT;	
}