/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez_home <ldutriez@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:51:17 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/06/22 12:48:23 by ldutriez_ho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int port, int com_domain, int sock_type)
{
	create_socket(com_domain, sock_type);
	init_addr_inputs(com_domain, port);
	connect_to_serv();
	// send_request("HONK");
	// receive_response();
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
	(void)file_path;
	send(_sockfd , "Hello World\n" , 12 , 0 );
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
