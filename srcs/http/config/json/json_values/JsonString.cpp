/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonString.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 12:09:31 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 19:17:28 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonString.hpp"


JsonString::JsonString(std::string value)
: _value(value)
{}

JsonString::JsonString(const JsonString & to_copy)
{
	*this = to_copy;
}

JsonString::~JsonString()
{}

JsonString &
JsonString::operator=(const JsonString & to_assign)
{
	if (this != & to_assign)
		_value = to_assign._value;
	return *this;
}

std::ostream &
operator<<(std::ostream & os, const JsonString & to_print)
{
	os << to_print._value;
}
