/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserAgent.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:51:17 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/09/21 10:07:31 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserAgent.hpp"

using namespace webclient;

UserAgent::UserAgent(int port, int com_domain, int sock_type)
{
	create_socket(com_domain, sock_type);
	init_addr_inputs(com_domain, port);
	connect_to_serv();
}

UserAgent::UserAgent(UserAgent const & src)
{
	(void)src;
}

UserAgent::~UserAgent(void)
{
	close(_sockfd);
}

UserAgent &
UserAgent::operator=(UserAgent const & src)
{
	this->_sockfd = src._sockfd;
	this->_address = src._address;
	return (*this);
}

int
UserAgent::getsockfd() const
{
	return (_sockfd);
}

void
UserAgent::create_socket(int domain, int type, int protocol)
{
	int	reuse = 0;
	int	result = 0;
	
	this->_sockfd = socket(domain, type, protocol);
	result = setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
	if (result == -1 || _sockfd == -1)
		throw UnableToCreateClientSocket();
	Logger(basic_type, minor_lvl) << "The Client socket's fd is " << _sockfd;
}

void
UserAgent::init_addr_inputs(int domain, int port)
{
	memset(&_address, 0, sizeof(_address));
	_target_port = port;
	_address.sin_family = domain;
	_address.sin_port = htons(port);
	if(inet_pton(AF_INET, "127.0.0.1", &_address.sin_addr) <= 0)
		Logger(error_type, error_lvl) << "Invalid address/ Address not supported";
}

void
UserAgent::connect_to_serv()
{
	if (connect(_sockfd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		Logger(error_type, error_lvl) << "Connection Failed";
		throw UnableToConnect();
	}
	Logger(basic_type, minor_lvl) << "The Client is connected to " << _target_port;
}

void
UserAgent::send_request(std::string file_path)
{
	std::ifstream	file(file_path);
	std::string		tmp;
	std::string		to_send;

	while (file.peek() != EOF)
	{
		std::getline(file, tmp);
		to_send += tmp + "\r\n";
	}
	to_send += "\r\n";
	
	file.close();
	
	send(_sockfd , to_send.c_str() , to_send.size() , 0);

	Logger(basic_type, minor_lvl) << "The Client sent :\n" << to_send;
}

void
UserAgent::receive_response()
{
	char buffer[1024] = {0};
	
	read(_sockfd , buffer, 1024);
	Logger(basic_type, minor_lvl) << "The Client received :\n" << buffer;
}

// EXCEPTIONS

UserAgent::UnableToCreateClientSocket::UnableToCreateClientSocket() throw()
: _msg("Unable to create a socket for the Client : ")
{
	_msg += strerror(errno);
}

UserAgent::UnableToCreateClientSocket::~UnableToCreateClientSocket() throw()
{}

const char *
UserAgent::UnableToCreateClientSocket::what() const throw()
{
	return _msg.c_str();
}

UserAgent::UnableToConnect::UnableToConnect() throw()
: _msg("Unable to set socket as listener : ")
{
	_msg += strerror(errno);
}

UserAgent::UnableToConnect::~UnableToConnect() throw()
{}

const char *
UserAgent::UnableToConnect::what() const throw()
{
	return _msg.c_str();
}