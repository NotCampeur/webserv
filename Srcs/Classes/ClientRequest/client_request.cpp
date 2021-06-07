/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:30:02 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/07 16:36:40 by ldutriez         ###   ########.fr       */
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
	#ifdef DEBUG
		std::cout << "Method -------> " << _method << std::endl;
	#endif
}

void	client_request::set_path(std::string &client_request)
{
	size_t	to_find(client_request.find("?"));
	
	if (to_find == std::string::npos)
	{
		to_find = client_request.find(" ");
		_path.assign(client_request.substr(0, to_find));
		client_request.erase(0, to_find + 1);
	}
	else
	{
		_path.assign(client_request.substr(0, to_find));
		client_request.erase(0, to_find + 1);
		set_query(client_request);
	}
	#ifdef DEBUG
		std::cout << "Path ---------> " << _path << std::endl;
	#endif
}

void	client_request::set_query(std::string &client_request)
{
	size_t	space(client_request.find(" "));
	
	_query.assign(client_request.substr(0, space));
	client_request.erase(0, space + 1);
	#ifdef DEBUG
		std::cout << "Query --------> " << _query << std::endl;
	#endif
}

void	client_request::set_HTTP_version(std::string &client_request)
{
	size_t	end_of_line(client_request.find("\n"));
	
	_HTTP_version.assign(client_request.substr(0, end_of_line - 1));
	client_request.erase(0, end_of_line + 1);
	#ifdef DEBUG
		std::cout << "HTTP_version -> " << _HTTP_version << std::endl;
	#endif
}

static size_t	find_body_start(std::string &client_request)
{
	size_t	result(std::string::npos);

	result = client_request.find("\n\r\n");
	result = (result == std::string::npos) ? client_request.size() : result;
	return (result);
}

void	client_request::set_headers(std::string &client_request)
{
	size_t	size(find_body_start(client_request));
	size_t	end_of_line;

	for (size_t i(0); i < size; i++)
	{
		end_of_line = client_request.find("\n");
		_headers.push_back(client_request.substr(0, end_of_line - 1));
		client_request.erase(0, end_of_line + 1);
		i += end_of_line;
	}
	#ifdef DEBUG
		size_t	size_debug(_headers.size());
		
		for (size_t i(0); i < size_debug; i++)
			std::cout << "Headers ------> " << _headers[i] << std::endl;
	#endif
}

void	client_request::set_body(std::string &client_request)
{
	size_t	size(client_request.size());
	size_t	end_of_line;

	for (size_t i(0); i < size; i++)
	{
		end_of_line = client_request.find("\n");
		_body.push_back(client_request.substr(0, end_of_line - 1));
		client_request.erase(0, end_of_line + 1);
	}
	#ifdef DEBUG
		for (size_t i(0); i < size; i++)
			std::cout << "Body ---------> " << _body[i] << std::endl;
	#endif
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
	set_HTTP_version(tmp);
	set_headers(tmp);
	set_body(tmp);
	#ifdef DEBUG
		std::cout << "Remaining : [" << tmp << "]" << std::endl;
	#endif
}

client_request::client_request(std::string &client_request)
{
	set_method(client_request);
	set_path(client_request);
	set_HTTP_version(client_request);
	set_headers(client_request);
	set_body(client_request);
	#ifdef DEBUG
		std::cout << "Remaining : [" << client_request << "]" << std::endl;
	#endif
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