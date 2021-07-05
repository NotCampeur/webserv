/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IJsonValue.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:38:36 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 15:56:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_VALUE_HPP
# define WEBSERV_JSON_VALUE_HPP

# include "webserv.hpp"

class IJsonValue
{
	public:
				IJsonValue();
		virtual	~IJsonValue() = 0;
};

#endif