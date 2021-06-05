/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:30:02 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/05 14:33:32 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

request::request()
{}

void	request::set_method(std::string &request)
{
	size_t	space(request.find(" "));
	
	_method.assign(request.substr(0, space));
	request.erase(0, space + 1);
	std::cout << "Method \"" << _method << "\"" << std::endl;
	std::cout << "request \"" << request << "\"" << std::endl;
}

void	request::set_path(std::string &request)
{
	(void)request;
}

void	request::set_query(std::string &request)
{
	(void)request;
}

void	request::set_HTTP_version(std::string &request)
{
	(void)request;
}

void	request::set_headers(std::string &request)
{
	(void)request;
}

void	request::set_body(std::string &request)
{
	(void)request;
}

request::request(const request &to_copy)
{
	*this = to_copy;
}

request::request(const char *request)
{
	std::string	tmp(request);

	set_method(tmp);
	set_path(tmp);
	set_query(tmp);
	set_HTTP_version(tmp);
	set_headers(tmp);
	set_body(tmp);
	std::cout << "Remaining : [" << tmp << "]" << std::endl;
}

request::request(std::string &request)
{
	set_method(request);
	set_path(request);
	set_query(request);
	set_HTTP_version(request);
	set_headers(request);
	set_body(request);
	std::cout << "Remaining : [" << request << "]" << std::endl;
}

request::~request()
{}

request	&request::operator=(const request &to_assign)
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