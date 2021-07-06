/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:53:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/06 14:32:41 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(JsonObject & config_object)
: _global_scope(config_object)
{}

Config::Config(const Config & to_copy)
: _global_scope(to_copy._global_scope)
{}

Config::~Config()
{}

Config & Config::operator=(const Config & to_assign)
{
	if (this != &to_assign)
		_global_scope = to_assign._global_scope;
	return *this;
}

std::ostream &
operator<<(std::ostream & os, const Config & to_print)
{
	os << "Config loaded :\n";
	os << to_print._global_scope;
	return os;
}
