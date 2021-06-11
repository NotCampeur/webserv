#include "ClientHandler.hpp"

ClientHandler::ClientHandler(const Client & client, HandlerTable & ht) :
_client(client),
_ht(ht)
{}

ClientHandler::ClientHandler(ClientHandler const & src) :
_client(src._client),
_ht(src._ht)
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

// Function TBU with request parsing and proper reading of header content
void 
ClientHandler::readable(void)
{
	char		read_buff[RECV_BUF_SIZE] = {0};
	ssize_t		bytes_read;

	bytes_read = recv(_client.getsockfd(), read_buff, RECV_BUF_SIZE, 0);
	if (bytes_read == -1)
		throw UnableToReadClientRequest();
	#ifdef DEBUG
		std::cout << "Socket content (" << bytes_read << " byte read): "
		<< read_buff << std::endl;
	#endif
}

void
ClientHandler::writable(void)
{
	std::string msg = "Hello World";
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
	
	#ifdef DEBUG
		std::cout << "Message written to client socket: " << get_clientfd() << " : " << msg << std::endl;
	#endif
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

const char *
ClientHandler::UnableToReadClientRequest::what() const throw()
{
	std::string err = "Unable to read to client socket: ";
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