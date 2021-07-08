/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IJsonValue.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:38:36 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/08 18:04:38 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_VALUE_HPP
# define WEBSERV_JSON_VALUE_HPP

class IJsonValue
{
	protected:
		std::string			_key;

	public:
							IJsonValue(std::string key) : _key(key) {};
							IJsonValue(const IJsonValue & to_copy) : _key(to_copy._key) {};
		virtual				~IJsonValue() {};

		virtual std::string	key(void) const = 0;

		virtual	IJsonValue	*clone(void) = 0;
		virtual void		print(int indent) const = 0;
};

#endif