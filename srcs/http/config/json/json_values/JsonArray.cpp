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
JsonArray::add_value(IJsonValue & to_add)
{
	_value.push_back(&to_add);
}

JsonArray &
JsonArray::operator=(const JsonArray & to_assign)
{}

std::ostream &
operator<<(std::ostream & os, const JsonArray & to_print)
{
	JsonArray::value_type::const_iterator	it(to_print._value.begin());
	JsonArray::value_type::const_iterator	ite(to_print._value.end());

	for (;it != ite; it++)
		os << *it;
}
