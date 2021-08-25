/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ValidatorConfig.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:12:50 by notcampeur        #+#    #+#             */
/*   Updated: 2021/08/25 21:15:08 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ValidatorConfig.hpp"

ValidatorConfig::ValidatorConfig()
: _root_dir("./"), _is_autoindex_on(false), _default_file_dir()
{}

ValidatorConfig::ValidatorConfig(const ValidatorConfig & to_copy)
: _root_dir(to_copy._root_dir), _is_autoindex_on(to_copy._is_autoindex_on)
, _default_file_dir(to_copy._default_file_dir)
{}

ValidatorConfig::~ValidatorConfig()
{}

//Getters
std::string
ValidatorConfig::root_dir() const
{
	return _root_dir;
}

bool
ValidatorConfig::is_autoindex_on() const
{
	return _is_autoindex_on;
}

std::string
ValidatorConfig::default_file_dir() const
{
	return _default_file_dir;
}

RouteMethod
ValidatorConfig::accepted_method() const
{
	return _accepted_method;
}

//Setters
void
ValidatorConfig::set_root_dir(std::string const &root_dir)
{
	_root_dir = root_dir;
}

void
ValidatorConfig::set_autoindex(bool is_autoindex_on)
{
	_is_autoindex_on = is_autoindex_on;
}

void
ValidatorConfig::set_default_file_dir(std::string const &default_file_dir)
{
	_default_file_dir = default_file_dir;
}

void
ValidatorConfig::set_accepted_method(RouteMethod value)
{
	_accepted_method = value;
}

//Operators

ValidatorConfig &
ValidatorConfig::operator=(const ValidatorConfig & to_assign)
{
	if (this != &to_assign)
	{
		_root_dir = to_assign._root_dir;
		_is_autoindex_on = to_assign._is_autoindex_on;
		_default_file_dir = to_assign._default_file_dir;
	}
	return *this;
}


ValidatorConfig &
ValidatorConfig::operator=(const RouteConfig & to_assign)
{
	_root_dir = to_assign.root();
	_is_autoindex_on = to_assign.is_autoindex_on();
	_default_file_dir = to_assign.default_file_dir();
	_accepted_method = to_assign.accepted_method();
	return *this;
}

ValidatorConfig &
ValidatorConfig::operator=(const ServerConfig & to_assign)
{
	_root_dir = to_assign.root_dir();
	_is_autoindex_on = to_assign.is_autoindex_on();
	_default_file_dir = *to_assign.default_file_dir();
	_accepted_method = GET;
	return *this;
}
