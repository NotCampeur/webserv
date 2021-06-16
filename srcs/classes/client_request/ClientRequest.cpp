/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:30:02 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/16 10:47:47 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"

ClientRequest::ClientRequest()
{}

void	ClientRequest::set_method(std::string &ClientRequest)
{
	size_t	space(ClientRequest.find(" "));
	
	_method.assign(ClientRequest.substr(0, space));
	ClientRequest.erase(0, space + 1);
	Logger(LOG_FILE, basic_type, minor_lvl) << "Method -------> " + _method;
}

void	ClientRequest::set_path(std::string &ClientRequest)
{
	size_t	to_find(ClientRequest.find("?"));
	
	if (to_find == std::string::npos)
	{
		to_find = ClientRequest.find(" ");
		_path.assign(ClientRequest.substr(0, to_find));
		ClientRequest.erase(0, to_find + 1);
	}
	else
	{
		_path.assign(ClientRequest.substr(0, to_find));
		ClientRequest.erase(0, to_find + 1);
		set_query(ClientRequest);
	}
	Logger(LOG_FILE, basic_type, minor_lvl) << "Path ---------> " + _path;
}

void	ClientRequest::set_query(std::string &ClientRequest)
{
	size_t	space(ClientRequest.find(" "));
	
	_query.assign(ClientRequest.substr(0, space));
	ClientRequest.erase(0, space + 1);
	Logger(LOG_FILE, basic_type, minor_lvl) << "Query --------> " + _query;
}

void	ClientRequest::set_HTTP_version(std::string &ClientRequest)
{
	size_t	end_of_line(ClientRequest.find("\n"));
	
	_HTTP_version.assign(ClientRequest.substr(0, end_of_line - 1));
	ClientRequest.erase(0, end_of_line + 1);
	Logger(LOG_FILE, basic_type, minor_lvl) << "HTTP_version -> " + _HTTP_version;
}

static size_t	find_body_start(std::string &ClientRequest)
{
	size_t	result(std::string::npos);

	result = ClientRequest.find("\n\r\n");
	result = (result == std::string::npos) ? ClientRequest.size() : result;
	return (result);
}

void	ClientRequest::set_headers(std::string &ClientRequest)
{
	size_t	size(find_body_start(ClientRequest));
	size_t	end_of_line;

	for (size_t i(0); i < size; i++)
	{
		end_of_line = ClientRequest.find("\n");
		_headers.push_back(ClientRequest.substr(0, end_of_line - 1));
		ClientRequest.erase(0, end_of_line + 1);
		i += end_of_line;
	}
	size_t	size_debug(_headers.size());
	for (size_t i(0); i < size_debug; i++)
		Logger(LOG_FILE, basic_type, minor_lvl) << "Headers ------> " + _headers[i];
}

void	ClientRequest::set_body(std::string &ClientRequest)
{
	size_t	size(ClientRequest.size());
	size_t	end_of_line;

	for (size_t i(0); i < size; i++)
	{
		end_of_line = ClientRequest.find("\n");
		_body.push_back(ClientRequest.substr(0, end_of_line - 1));
		ClientRequest.erase(0, end_of_line + 1);
	}
	for (size_t i(0); i < size; i++)
		Logger(LOG_FILE, basic_type, minor_lvl) << "Body ---------> " + _body[i];
}

ClientRequest::ClientRequest(const ClientRequest &to_copy)
{
	*this = to_copy;
}

ClientRequest::ClientRequest(const char *ClientRequest)
{
	std::string	tmp(ClientRequest);

	set_method(tmp);
	set_path(tmp);
	set_HTTP_version(tmp);
	set_headers(tmp);
	set_body(tmp);
	Logger(LOG_FILE, basic_type, minor_lvl) << "Remaining : [" + tmp + "]";
}

ClientRequest::ClientRequest(std::string &ClientRequest)
{
	set_method(ClientRequest);
	set_path(ClientRequest);
	set_HTTP_version(ClientRequest);
	set_headers(ClientRequest);
	set_body(ClientRequest);
	Logger(LOG_FILE, basic_type, minor_lvl) << "Remaining : [" + ClientRequest + "]";
}

ClientRequest::~ClientRequest()
{}

ClientRequest	&ClientRequest::operator=(const ClientRequest &to_assign)
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
