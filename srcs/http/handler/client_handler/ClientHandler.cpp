#include "ClientHandler.hpp"

ClientHandler::ClientHandler(const Client & client) :
_client(client)
{}

ClientHandler::ClientHandler(ClientHandler const & src) :
_client(src._client)
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
	if (_req_parser.iscomplete())
		return ;

	char		read_buff[RECV_BUF_SIZE] = {0};
	ssize_t		bytes_read;

	while (1)
	{
		bytes_read = recv(_client.getsockfd(), read_buff, RECV_BUF_SIZE, 0);
		if (bytes_read == -1)
			throw UnableToReadClientRequest();

		_req_parser.parse(read_buff, bytes_read);
		// Break conditions: buffer was not full after last read || req is complete (in which case, woud need to handle buffer leftovers if any)
		if (bytes_read < RECV_BUF_SIZE)
			break;
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "Socket content (" << bytes_read << " byte read): " << read_buff;
}

void
ClientHandler::writable(void)
{
	if (!_req_parser.iscomplete())
		return ;

	std::stringstream	ss;
	static std::string 	msg = "Hello World\n";
	ssize_t				bytes_written;

	try
	{
		set_header(ss, msg.size());
	}
	catch(const std::exception& e)
	{
		throw e;
	}

	ss << msg;
	std::string datagram = ss.str();

	bytes_written = send(get_clientfd(), datagram.c_str(), datagram.size(), 0);

	if (bytes_written != static_cast<ssize_t>(datagram.size()))
		throw UnableToWriteToClient();

	Logger(LOG_FILE, basic_type, minor_lvl) << "Message written to client socket: " << get_clientfd() << " : " << datagram;

	_req_parser.next_request();	
}

void
ClientHandler::set_header(std::stringstream & header, size_t content_length)
{	
	header << "HTTP/1.1 200 OK\r\n"
	<< "Content-Type: text\r\n"
	<< "Content-Length: "
	<< (content_length)
	<< "\r\n\r\n";
}

const char *
ClientHandler::UnableToReadClientRequest::what() const throw()
{
	std::string err = "Unable to read from client socket: ";
	err += strerror(errno);	

	return err.c_str();
}

const char *
ClientHandler::UnableToWriteToClient::what() const throw()
{
	std::string err = "Unable to write to client socket: ";
	err += strerror(errno);
	
	return err.c_str();
}
