/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonArray.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 21:01:56 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/16 22:49:08 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonArray.hpp"

JsonArray::JsonArray(std::string key)
: _key(key), _value()
{
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << "Begin of " << _key << " array";
}

JsonArray::JsonArray(const JsonArray & to_copy)
{
	*this = to_copy;
}

JsonArray::~JsonArray()
{
	value_type::iterator	it(_value.begin());
	value_type::iterator	ite(_value.end());

	for (;it != ite; it++)
		delete *it;
}

void
JsonArray::add_value(IJsonValue * to_add)
{
	_value.push_back(to_add);
}

std::string
JsonArray::key(void) const
{
	return _key;
}

JsonArray::value_type::const_iterator
JsonArray::value_begin(void) const
{
	return _value.begin();
}

JsonArray::value_type::const_iterator
JsonArray::value_end(void) const
{
	return _value.end();
}

IJsonValue *
JsonArray::clone(void)
{
	JsonArray	*result;

	result = new JsonArray(*this);
	return result;
}

void
JsonArray::print(int indent) const
{
	JsonArray::value_type::const_iterator	it(_value.begin());
	JsonArray::value_type::const_iterator	ite(_value.end());

	std::cout << "\n";
	for (int i(0); i < indent - 1; i++)
		std::cout << "    ";
	std::cout << "[\n";
	for (;it != ite; it++)
	{
		if (it != _value.begin())
			std::cout << ",\n";
		for (int i(0); i < indent; i++)
			std::cout << "    ";
		JsonString	*tmp = dynamic_cast<JsonString *>(*it);
		if (tmp != NULL)
			(*it)->print(0);
		else
			(*it)->print(indent + 1);
	}
	std::cout << "\n";
	for (int i(0); i < indent - 1; i++)
		std::cout << "    ";
	std::cout << "]";
}

void
JsonArray::print_to_buffer(int indent, std::string & buffer) const
{
	JsonArray::value_type::const_iterator	it(_value.begin());
	JsonArray::value_type::const_iterator	ite(_value.end());

	buffer += "\n";
	for (int i(0); i < indent - 1; i++)
		buffer += "    ";
	buffer += "[\n";
	for (;it != ite; it++)
	{
		if (it != _value.begin())
			buffer += ",\n";
		for (int i(0); i < indent; i++)
			buffer += "    ";
		JsonString	*tmp = dynamic_cast<JsonString *>(*it);
		if (tmp != NULL)
			(*it)->print_to_buffer(0, buffer);
		else
			(*it)->print_to_buffer(indent + 1, buffer);
	}
	buffer += "\n";
	for (int i(0); i < indent - 1; i++)
		buffer += "    ";
	buffer += "]";
}

JsonArray &
JsonArray::operator=(const JsonArray & to_assign)
{
	if (this != &to_assign)
	{
		value_type::const_iterator	it(to_assign._value.begin());
		value_type::const_iterator	ite(to_assign._value.end());

		for (;it != ite; it++)
			_value.push_back((*it)->clone());
	}
	return *this;
}

std::ostream &
operator<<(std::ostream & os, const JsonArray & to_print)
{
	to_print.print(1);
	return os;
}
