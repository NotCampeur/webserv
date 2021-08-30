/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonString.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 12:09:31 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/09 00:23:25 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonString.hpp"


JsonString::JsonString(std::string key, std::string value)
: _key(key), _value(value)
{}

JsonString::JsonString(const JsonString & to_copy)
{
	*this = to_copy;
}

JsonString::~JsonString()
{}

std::string
JsonString::key(void) const
{
	return _key;
}

std::string
JsonString::value(void) const
{
	return _value;
}

IJsonValue *
JsonString::clone(void)
{
	JsonString	*result;

	result = new JsonString(*this);
	return result;
}

void
JsonString::print(int indent) const
{
	for (int i(0); i < indent; i++)
		std::cout << "    ";
	std::cout << '"' + _value + '"';
}

void
JsonString::print_to_buffer(int indent, std::string &buffer) const
{
	for (int i(0); i < indent; i++)
		buffer += "    ";
	buffer += '"' + _value + '"';
}

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
	to_print.print(1);
	return os;
}
