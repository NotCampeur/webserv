/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/20 19:33:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int					create_socket(void)
{
	int	result(socket(AF_INET, SOCK_STREAM, 0));

	if (result == -1)
		throw strerror(errno);
	std::cout << "The server socket's fd is " << result << std::endl;
	return result;
}

struct sockaddr_in	init_addr_in(void)
{
	struct sockaddr_in	result;

	result.sin_family = AF_INET;
	result.sin_addr.s_addr = INADDR_ANY;
	result.sin_port = htons(PORT);
	for (int i(0); i < 8; i++)
		result.sin_zero[i] = '\0';
	return result;
}

void				naming_serv_socket(int socket, struct sockaddr_in addr)
{
	int	binding;

	binding = bind(socket, (struct sockaddr *)&addr, sizeof(addr));
	if (binding == -1)
	{
		throw strerror(errno);
	}
	std::cout << "The bind with the server is up" << std::endl;
}

void				set_listener(int serv_socket)
{
	int	open_to_connection(0);

	open_to_connection = listen(serv_socket, MAX_PENDING_CONNECTION);
	if (open_to_connection != 0)
		throw strerror(errno);
	std::cout << "The server socket is listening\n" << std::endl;
}

int					accept_connection(int listening_socket, struct sockaddr_in addr)
{
	int	result;
	int	addr_len = sizeof(addr);
	
	result = accept(listening_socket, (struct sockaddr *)&addr, (socklen_t *)&addr_len);
	if (result == -1)
		throw strerror(errno);
	std::cout << "A new connection has been acepted on fd : " << result << std::endl;
	return result;
}

void				get_client_request(int client_socket)
{
	char	client_socket_buff[1024] = {0};
	ssize_t	byte_readed(0);

	byte_readed = read(client_socket, client_socket_buff, 1024);
	if (byte_readed == -1)
		throw strerror(errno);
	std::cout << "Socket content (" << byte_readed << " byte readed):"
	<< std::endl << client_socket_buff;
}

void				send_header(const int client_socket, size_t content_length)
{
	int			byte_writed;
	std::string	header("HTTP/1.1 200 OK\nContent-Type: text\nContent-Length: ");
	header += content_length;
	header += "\n\n";
	byte_writed = write(client_socket, header.c_str(), header.size());
	if (byte_writed == -1)
		throw strerror(errno);
}

void				send_response(const int client_socket, const std::string &msg)
{
	int	byte_writed;

	send_header(client_socket, msg.size());
	byte_writed = write(client_socket, msg.c_str(), msg.size());
	if (byte_writed == -1)
		throw strerror(errno);
}

void				connection_handler(int server_socket, struct sockaddr_in addr)
{
	int 	client_socket(0);
	bool	error(false);

	while (error == false)
	{
		client_socket = accept_connection(server_socket, addr);
		try
		{
			get_client_request(client_socket);
			send_response(client_socket, "<iframe width=\"1200\" height=\"800\"\nsrc=https://www.youtube.com/embed/dQw4w9WgXcQ?autoplay=1&mute=1>\n</iframe>");
		}
		catch(const char *e)
		{
			error = true;
			std::cerr << "Error : " << e << "." << std::endl;
		}
		close(client_socket);
	}
}

int					main(void)
{
	try
	{
		int					server_socket(create_socket());
		struct sockaddr_in	addr(init_addr_in());
		
		try
		{
			naming_serv_socket(server_socket, addr);
			set_listener(server_socket);
			connection_handler(server_socket, addr);
		}
		catch(const char *e)
		{
			std::cerr << "Error : " << e << "." << std::endl;
		}
		close(server_socket);
	}
	catch(const char *e)
	{
		std::cerr << "Error : " << e << "." << std::endl;
	}
	return 0;
}
