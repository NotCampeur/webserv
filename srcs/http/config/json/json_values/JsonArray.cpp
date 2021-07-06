/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonArray.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:27:02 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 15:24:11 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonArray.hpp"

JsonArray::JsonArray()
{}

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
