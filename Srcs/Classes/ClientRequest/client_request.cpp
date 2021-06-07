/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:30:02 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/07 14:14:36 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_request.hpp"

client_request::client_request()
{}

void	client_request::set_method(std::string &client_request)
{
	size_t	space(client_request.find(" "));
	
	_method.assign(client_request.substr(0, space));
	client_request.erase(0, space + 1);
	std::cout << "Method \"" << _method << "\"" << std::endl;
}

void	client_request::set_path(std::string &client_request)
{
	(void)client_request;
}

void	client_request::set_query(std::string &client_request)
{
	(void)client_request;
}

void	client_request::set_HTTP_version(std::string &client_request)
{
	(void)client_request;
}

void	client_request::set_headers(std::string &client_request)
{
	(void)client_request;
}

void	client_request::set_body(std::string &client_request)
{
	(void)client_request;
}

client_request::client_request(const client_request &to_copy)
{
	*this = to_copy;
}

client_request::client_request(const char *client_request)
{
	std::string	tmp(client_request);

	set_method(tmp);
	set_path(tmp);
	set_query(tmp);
	set_HTTP_version(tmp);
	set_headers(tmp);
	set_body(tmp);
	std::cout << "Remaining : [" << tmp << "]" << std::endl;
	std::cout << "client_request \"" << client_request << "\"" << std::endl;
}

client_request::client_request(std::string &client_request)
{
	set_method(client_request);
	set_path(client_request);
	set_query(client_request);
	set_HTTP_version(client_request);
	set_headers(client_request);
	set_body(client_request);
	std::cout << "Remaining : [" << client_request << "]" << std::endl;
}

client_request::~client_request()
{}

client_request	&client_request::operator=(const client_request &to_assign)
{
	if (this != &to_assign)
	{
		_method = to_assign._method;
		_path = to_assign._path;
		_query = to_assign._query;
		_HTTP_version = to_assign._HTTP_version;
		_headers = to_assign._headers;
		_body = to_assign._body;
	}
	return *this;
}