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

ClientHandler &
ClientHandler::operator=(ClientHandler const & src)
{
    return (*this);
}

int
ClientHandler::getfd(void) const
{
    return _client.getfd();
}

void 
ClientHandler::readable(void)
{
	char		read_buff[RECV_BUF_SIZE] = {0};
	ssize_t		bytes_read;

	bytes_read = recv(_client.getfd(), read_buff, RECV_BUF_SIZE, 0);
	if (bytes_read == -1)
		throw UnableToGetClientRequest();
	#ifdef DEBUG
		std::cout << "Socket content (" << bytes_read << " byte readed):"
		<< std::endl << client_socket_buff;
	#endif
}

void
ClientHandler::writable(void)
{
	// int	bytes_written;

	// try
	// {
	// 	send_header(msg.size());
	// }
	// catch(const std::exception& e)
	// {
	// 	throw e;
	// }
	// byte_writed = write(_client_socket.back(), msg.c_str(), msg.size());
	// if (byte_writed == -1)
	// 	throw UnableToWriteToClient();
}

void
ClientHandler::send_header(size_t content_length)
{
	// int	byte_writed;
	
	// std::string	header("HTTP/1.1 200 OK\nContent-Type: text\nContent-Length: ");
	// header += content_length;
	// header += "\n\n";
	// byte_writed = write(_client_socket.back(), header.c_str(), header.size());
	// if (byte_writed == -1)
	// 	throw UnableToWriteToClient();
}

const char *
ClientHandler::UnableToGetClientRequest::what() const throw()
{
    return (std::string(std::string("Unable to get client request : ")
    + std::string(strerror(errno)))).c_str();
}