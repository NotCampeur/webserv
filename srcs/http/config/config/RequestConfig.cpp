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
	_error_pages(serv_conf.get_all_error_pages()),
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