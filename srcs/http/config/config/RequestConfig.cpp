/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestConfig.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:12:50 by notcampeur        #+#    #+#             */
/*   Updated: 2021/09/02 04:20:29 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestConfig.hpp"

RequestConfig::RequestConfig()
: _error_pages(), _max_client_body_size(1000000)
, _locations()
, _accepted_method(GET), _redirection(), _root()
, _is_autoindex_on(false), _default_file_dir()
, _cgi(), _upload_path()
{}

RequestConfig::RequestConfig(const RequestConfig & to_copy)
: _error_pages(to_copy._error_pages)
, _max_client_body_size(to_copy._max_client_body_size)
, _locations(to_copy._locations)
, _accepted_method(to_copy._accepted_method)
, _redirection(to_copy._redirection), _root(to_copy._root)
, _is_autoindex_on(to_copy._is_autoindex_on)
, _default_file_dir(to_copy._default_file_dir)
, _cgi(to_copy._cgi), _upload_path(to_copy._upload_path)
{}

RequestConfig::~RequestConfig()
{
	for (std::vector<LocationConfig *>::const_iterator it = _locations.begin()
		; it != _locations.end()
		; ++it)
	{
		delete *it;
	}
}

//Getters
std::string
RequestConfig::name(void) const
{
	return _name;
}

std::string
RequestConfig::ip(void) const
{
	return _ip;
}

std::string
RequestConfig::port(void) const
{
	return _port;
}

std::map<int, std::string>
RequestConfig::error_pages(void) const
{
	return _error_pages;
}

size_t
RequestConfig::max_client_body_size(void) const
{
	return _max_client_body_size;
}

const std::vector<LocationConfig *> &
RequestConfig::locations(void) const
{
	return _locations;
}

HTTPMethod
RequestConfig::accepted_method() const
{
	return _accepted_method;
}

std::pair<int, std::string>
RequestConfig::redirection(void) const
{
	return _redirection;
}

std::string
RequestConfig::root() const
{
	return _root;
}

bool
RequestConfig::is_autoindex_on() const
{
	return _is_autoindex_on;
}

std::string
RequestConfig::default_file_dir() const
{
	return _default_file_dir;
}

std::map<std::string, std::string>
RequestConfig::cgi(void) const
{
	return _cgi;
}

std::string
RequestConfig::upload_path(void) const
{
	return _upload_path;
}

//Setters
// void
// RequestConfig::set_error_pages(std::map<int, std::string> error_pages)
// {
// 	_error_pages = error_pages;
// }

// void
// RequestConfig::add_error_pages(int error, const std::string & page_path)
// {
// 	_error_pages[error] = page_path;
// }

// void
// RequestConfig::set_max_client_body_size(size_t max_size)
// {
// 	_max_client_body_size = max_size;
// }

// void
// RequestConfig::set_accepted_method(const HTTPMethod & accepted_method)
// {
// 	_accepted_method = accepted_method;
// }

// void
// RequestConfig::set_redirection(std::pair<int, std::string> & redirection)
// {
// 	_redirection = redirection;
// }

// void
// RequestConfig::set_root(const std::string & root_path)
// {
// 	_root = root_path;
// }

// void
// RequestConfig::set_is_autoindex_on(bool is_autoindex_on)
// {
// 	_is_autoindex_on = is_autoindex_on;
// }

// void
// RequestConfig::set_default_file_dir(const std::string & default_file_dir)
// {
// 	_default_file_dir = default_file_dir;
// }

// void
// RequestConfig::set_cgi(const std::map<std::string, std::string> & cgi)
// {
// 	_cgi = cgi;
// }

// void
// RequestConfig::set_upload_path(const std::string & upload_path)
// {
// 	_upload_path = upload_path;
// }

//Operators
RequestConfig &
RequestConfig::operator=(const RequestConfig & to_assign)
{
	if (this != &to_assign)
	{
		_error_pages = to_assign._error_pages;
		_max_client_body_size = to_assign._max_client_body_size;
		_accepted_method = to_assign._accepted_method;
		_redirection = to_assign._redirection;
		_root = to_assign._root;
		_is_autoindex_on = to_assign._is_autoindex_on;
		_default_file_dir = to_assign._default_file_dir;
		_cgi = to_assign._cgi;
		_upload_path = to_assign._upload_path;
	}
	return *this;
}

RequestConfig &
RequestConfig::operator=(const LocationConfig & to_assign)
{
	_accepted_method = to_assign.accepted_method();
	_redirection = to_assign.redirection();
	_root = to_assign.root();
	_is_autoindex_on = to_assign.is_autoindex_on();
	_default_file_dir = to_assign.default_file_dir();
	_cgi = to_assign.cgi();
	_upload_path = to_assign.upload_path();
	return *this;
}

RequestConfig &
RequestConfig::operator=(const ServerConfig & to_assign)
{
	_name = to_assign.name();
	_ip = to_assign.ip();
	_port = to_assign.port();
	_error_pages = to_assign.error_page_path();
	_max_client_body_size = to_assign.max_client_body_size();
	// Deep copy the server's locations.
	for (std::vector<LocationConfig *>::const_iterator it = to_assign.locations().begin()
		; it != to_assign.locations().end()
		; ++it)
	{
		_locations.push_back(new LocationConfig(*(*it)));
	}

	_locations = to_assign.locations();
	return *this;
}
