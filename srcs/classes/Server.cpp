/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:29:43 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/24 16:37:50 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

					Server::Server(const bool &verbose_state) : _client_header()
{
	_is_verbose = verbose_state;
	create_socket();
	init_addr_in();
	naming_serv_socket();
	set_listener();
	_client_socket = 0;
}

					Server::Server(const Server &to_copy)
{
	*this = to_copy;
}

					Server::~Server()
{
	if (_socket != 0)
		close(_socket);
	if (_client_socket != 0)
		close(_client_socket);
}

void				Server::set_verbose(const bool &state)
{
	_is_verbose = state;
}

void				Server::connection_handler()
{
	while (1)
	{
		accept_connection();
		get_client_request();
		send_response("<iframe width=\"1200\" height=\"800\" src=\"https://www.youtube.com/embed/Z3w5gVM_4y8?controls=0\" title=\"YouTube video player\" frameborder=\"0\" allow=\"accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture\" allowfullscreen></iframe>");
		close(_client_socket);
	}
}

void				Server::create_socket()
{
	int	reuse(1);
	int	result(0);
	
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	result = setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
	if (result == -1 || _socket == -1)
		throw UnableToCreateServerSocket();
	if (_is_verbose == true)
		std::cout << "The server socket's fd is " << _socket << std::endl;
}

void				Server::init_addr_in()
{
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(PORT);
	for (int i(0); i < 8; i++)
		_address.sin_zero[i] = '\0';
}

void				Server::naming_serv_socket()
{
	int	binding;

	binding = bind(_socket, (struct sockaddr *)&_address, sizeof(_address));
	if (binding == -1)
		throw UnableToNameSocket();
	if (_is_verbose == true)
		std::cout << "The bind with the server is up" << std::endl;
}

void				Server::set_listener()
{
	int	open_to_connection(0);

	open_to_connection = listen(_socket, MAX_PENDING_CONNECTION);
	if (open_to_connection == -1)
		throw UnableToSetListener();
	if (_is_verbose == true)
		std::cout << "The server socket is listening\n" << std::endl;
}

void				Server::get_client_request()
{
	char	client_socket_buff[1024] = {0};
	ssize_t	byte_readed(0);

	byte_readed = read(_client_socket, client_socket_buff, 1024);
	if (byte_readed == -1)
		throw UnableToGetClientRequest();
	if (_is_verbose == true)
		std::cout << "Socket content (" << byte_readed << " byte readed):"
		<< std::endl << client_socket_buff;

}

void				Server::send_header(size_t content_length)
{
	int	byte_writed;
	
	std::string	header("HTTP/1.1 200 OK\nContent-Type: text\nContent-Length: ");
	header += content_length;
	header += "\n\n";
	byte_writed = write(_client_socket, header.c_str(), header.size());
	if (byte_writed == -1)
		throw UnableToWriteToClient();

}

void				Server::send_response(const std::string &msg)
{
	int	byte_writed;

	send_header(msg.size());
	byte_writed = write(_client_socket, msg.c_str(), msg.size());
	if (byte_writed == -1)
		throw UnableToWriteToClient();

}

void				Server::accept_connection()
{
	int	addr_len = sizeof(_address);
	
	_client_socket = accept(_socket, (struct sockaddr *)&_address, (socklen_t *)&addr_len);
	if (_client_socket == -1)
		throw UnableToAcceptConnection();
	if (_is_verbose == true)
		std::cout << "A new connection has been acepted on fd : " << _client_socket << std::endl;
	
}

Server				&Server::operator=(const Server &to_assign)
{
	if (this != &to_assign)
	{
		_socket = to_assign._socket;
		_client_socket = to_assign._client_socket;
		_address = to_assign._address;
		_is_verbose = to_assign._is_verbose;
	}
	return *this;
}
