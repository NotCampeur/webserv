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

RequestConfig::RequestConfig(const ServerConfig & serv_conf, const LocationConfig & loc_conf) :
	_name(serv_conf.name()),
	_ip(serv_conf.ip()),
	_port(serv_conf.port()),
	_error_pages(serv_conf.error_page_path()),
	_max_client_body_size(serv_conf.max_client_body_size()),

	_accepted_method(loc_conf.accepted_method()),
	_redirection(loc_conf.redirection()),
	_root(loc_conf.root()),
	_is_autoindex_on(loc_conf.is_autoindex_on()),
	_default_file_dir(loc_conf.default_file_dir()),
	_cgi(loc_conf.cgi()),
	_upload_path(loc_conf.upload_path()),
	_path(loc_conf.path())
	{};


// RequestConfig::RequestConfig()
// : _error_pages(), _max_client_body_size(1000000)
// , _locations()
// , _accepted_method(GET), _redirection(), _root()
// , _is_autoindex_on(false), _default_file_dir()
// , _cgi(), _upload_path()
// {}

// RequestConfig::RequestConfig(const RequestConfig & to_copy)
// {
// 	*this = to_copy;
// }

RequestConfig::~RequestConfig()
{
}

//Getters
const std::string &
RequestConfig::name(void) const
{
	return _name;
}

const std::string &
RequestConfig::ip(void) const
{
	return _ip;
}

const std::string &
RequestConfig::port(void) const
{
	return _port;
}

const std::map<int, std::string> &
RequestConfig::error_pages(void) const
{
	return _error_pages;
}

size_t
RequestConfig::max_client_body_size(void) const
{
	return _max_client_body_size;
}

// const std::vector<LocationConfig *> &
// RequestConfig::locations(void) const
// {
// 	return _locations;
// }

const HTTPMethod &
RequestConfig::accepted_method() const
{
	return _accepted_method;
}

const std::pair<int, std::string> &
RequestConfig::redirection(void) const
{
	return _redirection;
}

const std::string &
RequestConfig::root() const
{
	return _root;
}

bool
RequestConfig::is_autoindex_on() const
{
	return _is_autoindex_on;
}

const std::string &
RequestConfig::default_file_dir() const
{
	return _default_file_dir;
}

const std::map<std::string, std::string> &
RequestConfig::cgi(void) const
{
	return _cgi;
}

const std::string &
RequestConfig::upload_path(void) const
{
	return _upload_path;
}

const std::string &
RequestConfig::location_path(void) const
{
	return _path;
}

//Operators
// RequestConfig &
// RequestConfig::operator=(const RequestConfig & to_assign)
// {
// 	if (this != &to_assign)
// 	{
// 		_error_pages = to_assign._error_pages;
// 		_max_client_body_size = to_assign._max_client_body_size;
// 		for (size_t i(0); i < to_assign._locations.size(); i++)
// 			_locations.push_back(new LocationConfig(*to_assign._locations[i]));
// 		_accepted_method = to_assign._accepted_method;
// 		_redirection = to_assign._redirection;
// 		_root = to_assign._root;
// 		_is_autoindex_on = to_assign._is_autoindex_on;
// 		_default_file_dir = to_assign._default_file_dir;
// 		_cgi = to_assign._cgi;
// 		_upload_path = to_assign._upload_path;
// 	}
// 	return *this;
// }


// RequestConfig &
// RequestConfig::operator=(const LocationConfig & to_assign)
// {
// 	_accepted_method = to_assign.accepted_method();
// 	_redirection = to_assign.redirection();
// 	_root = to_assign.root();
// 	_is_autoindex_on = to_assign.is_autoindex_on();
// 	_default_file_dir = to_assign.default_file_dir();
// 	_cgi = to_assign.cgi();
// 	_upload_path = to_assign.upload_path();
// 	return *this;
// }

// RequestConfig &
// RequestConfig::operator=(const ServerConfig & to_assign)
// {
// 	_name = to_assign.name();
// 	_ip = to_assign.ip();
// 	_port = to_assign.port();
// 	_error_pages = to_assign.error_page_path();
// 	_max_client_body_size = to_assign.max_client_body_size();
// 	for (size_t i(0); i < to_assign.locations().size(); i++)
// 		_locations.push_back(new LocationConfig(*to_assign.locations()[i]));
// 	return *this;
// }
