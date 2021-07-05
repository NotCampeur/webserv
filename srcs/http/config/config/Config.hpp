/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:35:39 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 16:53:02 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONFIG_HPP
# define WEBSERV_CONFIG_HPP

# include "webserv.hpp"
# include "JsonObject.hpp"

class Config
{
		JsonObject	& _global_scope;
		
	public:
		Config(JsonObject & config_object);
		Config(const Config & to_copy);
		~Config();

		Config & operator=(const Config & to_assign);
		friend std::ofstream & operator<<(std::ofstream & os,
											const Config & to_print);
};

#endif
