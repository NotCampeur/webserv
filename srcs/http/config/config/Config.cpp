/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:53:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 17:55:40 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(JsonObject & config_object)
: _global_scope(config_object)
{}

Config::Config(const Config & to_copy)
{
	*this = to_copy;
}

Config::~Config()
{}

Config & Config::operator=(const Config & to_assign)
{
	if (this != &to_assign)
		_global_scope = to_assign._global_scope;
	return *this;
}

std::ofstream &
operator<<(std::ofstream & os, const Config & to_print)
{
	os << to_print._global_scope;
}
