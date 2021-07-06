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

IJsonValue *
JsonObject::clone(void)
{
	JsonObject	*result;

	result = new JsonObject(*this);
	return result;
}

void
JsonObject::print(int indent) const
{
	JsonObject::value_type::const_iterator it = _value.begin();
	JsonObject::value_type::const_iterator ite = _value.end();
	
	std::cout << "{\n";
	for (; it != ite; it++)
	{
		if (it != _value.begin())
			std::cout << ",\n";
		for (int i(0); i < indent; i++)
			std::cout << "    ";
		std::cout << '"' << it->first << "\":";
		JsonString	*tmp = dynamic_cast<JsonString *>(it->second);
		if (tmp != NULL)
			it->second->print(0);
		else
			it->second->print(indent + 1);
	}
	std::cout << "\n";
	for (int i(0); i < indent - 1; i++)
		std::cout << "    ";
	std::cout << "}";
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
	to_print.print(1);
	return os;
}

JsonObject::MultipleDefinitionOfAValue::MultipleDefinitionOfAValue(std::string value) throw()
: _msg("Redefinition of " + value)
{}

JsonObject::MultipleDefinitionOfAValue::~MultipleDefinitionOfAValue() throw()
{}

const char *
JsonObject::MultipleDefinitionOfAValue::what() const throw()
{
	return _msg.c_str();
}
