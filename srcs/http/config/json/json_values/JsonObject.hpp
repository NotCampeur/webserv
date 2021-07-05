/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonObject.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:53:05 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 14:04:54 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_OBJECT_HPP
# define WEBSERV_JSON_OBJECT_HPP

# include "webserv.hpp"
# include "IJsonValue.hpp"

class JsonObject : public IJsonValue
{
	public:
		typedef std::map<std::string, IJsonValue *> value_type;

	private:
		value_type				_value;
	
	public:
								JsonObject();
								JsonObject(const JsonObject & to_copy);
								~JsonObject();

		void					add_value(std::string key, IJsonValue & to_add);
		void					add_value(std::pair<std::string, IJsonValue *> &to_add);

		JsonObject				&operator=(const JsonObject & to_assign);
		friend std::ostream		&operator<<(std::ostream & os,
												const JsonObject & to_print);

		class MultipleDefinitionOfAValue
		{
				std::string	_msg;
			public:
				MultipleDefinitionOfAValue(std::string value) throw();
				~MultipleDefinitionOfAValue() throw();

				const char * what() throw();
		};
};

#endif