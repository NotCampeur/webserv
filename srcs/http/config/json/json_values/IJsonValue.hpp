/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IJsonValue.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:38:36 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/06 22:29:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_VALUE_HPP
# define WEBSERV_JSON_VALUE_HPP

class IJsonValue
{
	public:
		virtual	~IJsonValue() {};

		virtual	IJsonValue	*clone(void) = 0;
		virtual void		print(int indent) const = 0;
};

#endif