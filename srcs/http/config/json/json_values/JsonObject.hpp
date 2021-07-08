/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:27:48 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/09 00:28:54 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_OBJECT_HPP
# define WEBSERV_JSON_OBJECT_HPP

# include "webserv.hpp"
# include "IJsonValue.hpp"
# include "JsonString.hpp"

class JsonObject : public IJsonValue
{
	public:
		typedef std::map<std::string, IJsonValue *> value_type;

	private:
		std::string				_key;
		value_type				_value;
	
	public:
								JsonObject(std::string key = "config");
								JsonObject(const JsonObject & to_copy);
								~JsonObject();

		void					add_value(std::string key, IJsonValue & to_add);
		void					add_value(std::pair<std::string, IJsonValue *> &to_add);

		std::string				key(void) const;

		IJsonValue				*clone(void);
		void					print(int indent) const;
		void					print_to_buffer(int indent, std::string & buffer) const;

		value_type::const_iterator	value_begin(void) const;
		value_type::const_iterator	value_end(void) const;

		JsonObject				&operator=(const JsonObject & to_assign);
		friend std::ostream		&operator<<(std::ostream & os,
												const JsonObject & to_print);

		class MultipleDefinitionOfAValue : public std::exception
		{
				std::string	_msg;
			public:
				MultipleDefinitionOfAValue(std::string value) throw();
				~MultipleDefinitionOfAValue() throw();

				const char * what() const throw();
		};
};

#endif