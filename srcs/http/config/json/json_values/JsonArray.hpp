/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonArray.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:55:58 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 14:49:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_ARRAY_HPP
# define WEBSERV_JSON_ARRAY_HPP

# include "webserv.hpp"
# include "IJsonValue.hpp"
# include "JsonString.hpp"

class JsonArray : public IJsonValue
{
	public:
		typedef std::vector<IJsonValue *> value_type;

	private:
		std::string					_key;
		std::vector<IJsonValue *>	_value;
	
	public:
								JsonArray(std::string key);
								JsonArray(const JsonArray & to_copy);
								~JsonArray();

		void					add_value(IJsonValue * to_add);

		std::string				key(void) const;
	
		value_type::const_iterator	value_begin(void) const;
		value_type::const_iterator	value_end(void) const;

		IJsonValue				*clone(void);
		void					print(int indent) const;
		void					print_to_buffer(int indent, std::string & buffer) const;

		JsonArray				&operator=(const JsonArray & to_assign);
		friend std::ostream		&operator<<(std::ostream & os,
									const JsonArray & to_print);
};

#endif