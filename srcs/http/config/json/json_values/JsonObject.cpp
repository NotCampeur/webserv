/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonObject.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 12:12:03 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 15:55:12 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonObject.hpp"


JsonObject::JsonObject()
{}

JsonObject::JsonObject(const JsonObject & to_copy)
{
	*this = to_copy;
}

JsonObject::~JsonObject()
{
	value_type::const_iterator it = _value.begin();
	value_type::const_iterator ite = _value.end();
	for (; it != ite; it++)
		delete it->second;
}

void
JsonObject::add_value(std::string key, IJsonValue & to_add)
{
	std::pair<value_type::iterator, bool> result;
	
	result = _value.insert(std::pair<std::string, IJsonValue *>(key, &to_add));
	if (result.second == false)
		throw MultipleDefinitionOfAValue(key);
}

void
JsonObject::add_value(std::pair<std::string, IJsonValue *> & to_add)
{
	std::pair<value_type::iterator, bool> result;
	
	result = _value.insert(to_add);
	if (result.second == false)
		throw MultipleDefinitionOfAValue(to_add.first);
}

JsonObject &
JsonObject::operator=(const JsonObject & to_assign)
{
	if (this != &to_assign)
	{
		value_type::const_iterator it = to_assign._value.begin();
		value_type::const_iterator ite = to_assign._value.end();
		for (; it != ite; it++)
			_value.insert(*it);
	}
	return *this;
}

std::ostream	&
operator<<(std::ostream & os, const JsonObject & to_print)
{
	JsonObject::value_type::const_iterator it = to_print._value.begin();
	JsonObject::value_type::const_iterator ite = to_print._value.end();
	
	for (; it != ite; it++)
		os << it->second;
}

JsonObject::MultipleDefinitionOfAValue::MultipleDefinitionOfAValue(std::string value) throw()
: _msg("Redefinition of " + value)
{}

JsonObject::MultipleDefinitionOfAValue::~MultipleDefinitionOfAValue() throw()
{}

const char *
JsonObject::MultipleDefinitionOfAValue::what() throw()
{
	return _msg.c_str();
}
