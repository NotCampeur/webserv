/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonString.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:50:28 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 14:00:39 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_STRING_HPP
# define WEBSERV_JSON_STRING_HPP

# include "webserv.hpp"
# include "IJsonValue.hpp"

class JsonString : public IJsonValue
{
		std::string		_value;
		
	public:
								JsonString(std::string value);
								JsonString(const JsonString & to_copy);
								~JsonString();

		JsonString			& operator=(const JsonString & to_assign);
		friend std::ostream	& operator<<(std::ostream & os,
									const JsonString & to_print);
};

#endif
