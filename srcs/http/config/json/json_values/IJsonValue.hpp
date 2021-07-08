/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IJsonValue.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:38:36 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/08 20:24:14 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_VALUE_HPP
# define WEBSERV_JSON_VALUE_HPP

# include "Logger.hpp"

class IJsonValue
{
	public:
		virtual				~IJsonValue() {};

		virtual std::string	key(void) const = 0;

		virtual	IJsonValue	*clone(void) = 0;
		virtual void		print(int indent) const = 0;
		virtual void		print_to_buffer(int indent, std::string &buffer) const = 0;
};


#endif