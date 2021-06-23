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
	char		read_buff[RECV_BUF_SIZE] = {0};
	ssize_t		bytes_read;

	bytes_read = recv(_client.getsockfd(), read_buff, RECV_BUF_SIZE, 0);
	if (bytes_read == -1)
		throw UnableToReadClientRequest();
	Logger(LOG_FILE, basic_type, minor_lvl) << "Socket content (" << bytes_read << " byte read): "
			<< read_buff;
}

void
ClientHandler::writable(void)
{
	std::string msg = "Hello World\n";
	ssize_t		bytes_written;

	try
	{
		send_header(msg.size());
	}
	catch(const std::exception& e)
	{
		throw e;
	}
	bytes_written = send(get_clientfd(), msg.c_str(), msg.size(), 0);
	if (bytes_written != static_cast<ssize_t>(msg.size()))
		throw UnableToWriteToClient();
	Logger(LOG_FILE, basic_type, minor_lvl) << "Message written to client socket: " << get_clientfd() << " : " << msg;
}

void
ClientHandler::send_header(size_t content_length)
{
	int	bytes_written;
	
	std::string	header = "HTTP/1.1 200 OK\nContent-Type: text\nContent-Length: ";
	header += content_length;
	header += "\n\n";
	bytes_written = send(get_clientfd(), header.c_str(), header.size(), 0);
	if (bytes_written == -1)
		throw UnableToWriteToClient();
}

ClientHandler::UnableToReadClientRequest::UnableToReadClientRequest() throw()
: _msg("Unable to read from client socket: ")
{
	_msg += strerror(errno);
}

ClientHandler::UnableToReadClientRequest::~UnableToReadClientRequest() throw()
{}

const char *
ClientHandler::UnableToReadClientRequest::what(void) const throw()
{
	return _msg.c_str();
}

ClientHandler::UnableToWriteToClient::UnableToWriteToClient() throw()
: _msg("Unable to write to client socket: ")
{
	_msg += strerror(errno);
}

ClientHandler::UnableToWriteToClient::~UnableToWriteToClient() throw()
{}

const char *
ClientHandler::UnableToWriteToClient::what(void) const throw()
{
	return _msg.c_str();
}
