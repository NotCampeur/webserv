/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:51:17 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/06/22 17:17:03 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

using namespace webclient;

Client::Client(int port, int com_domain, int sock_type)
{
	create_socket(com_domain, sock_type);
	init_addr_inputs(com_domain, port);
	connect_to_serv();
}

Client::Client(Client const & src)
{
	(void)src;
}

Client::~Client(void)
{
	close(_sockfd);
}

Client &
Client::operator=(Client const & src)
{
	this->_sockfd = src._sockfd;
	this->_address = src._address;
	return (*this);
}

int
Client::getsockfd() const
{
	return (_sockfd);
}

void
Client::create_socket(int domain, int type, int protocol)
{
	int	reuse = 0;
	int	result = 0;
	
	this->_sockfd = socket(domain, type, protocol);
	result = setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
	if (result == -1 || _sockfd == -1)
		throw UnableToCreateClientSocket();
	Logger(LOG_FILE, basic_type, minor_lvl) << "The Client socket's fd is " << _sockfd;
}

void
Client::init_addr_inputs(int domain, int port)
{
	memset(&_address, 0, sizeof(_address));
	_target_port = port;
	_address.sin_family = domain;
	_address.sin_port = htons(port);
	if(inet_pton(AF_INET, "127.0.0.1", &_address.sin_addr) <= 0)
		Logger(LOG_FILE, error_type, error_lvl) << "Invalid address/ Address not supported";
}

void
Client::connect_to_serv()
{
	if (connect(_sockfd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		Logger(LOG_FILE, error_type, error_lvl) << "Connection Failed";
		throw UnableToConnect();
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "The Client is connected to " << _target_port;
}

void
Client::send_request(std::string file_path)
{
	std::ifstream	file(file_path);
	std::string		tmp;
	std::string		to_send;

	while (file.peek() != EOF)
	{
		std::getline(file, tmp);
		to_send += tmp + "\n";
	}
	send(_sockfd , to_send.c_str() , to_send.size() , 0);
	file.close();
}

void
Client::receive_response()
{
	char buffer[1024] = {0};
	
	read(_sockfd , buffer, 1024);
	Logger(LOG_FILE, basic_type, minor_lvl) << "The Client received :\n" << buffer;
}

// EXCEPTIONS

const char *
Client::UnableToCreateClientSocket::what() const throw()
{
	std::string err = "Unable to create a socket for the Client : ";
	err += strerror(errno);

	return err.c_str();
}

const char *
Client::UnableToConnect::what() const throw()
{
	std::string err = "Unable to set socket as listener : ";
	err += strerror(errno);

	return err.c_str();
}
