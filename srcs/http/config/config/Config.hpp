/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:35:39 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/09 00:43:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONFIG_HPP
# define WEBSERV_CONFIG_HPP

# include "webserv.hpp"
# include "InitiationDispatcher.hpp"
# include "Server.hpp"
# include "JsonObject.hpp"
# include "JsonArray.hpp"
# include "JsonString.hpp"

class Config
{
	private:
		enum global_config
		{
			server,
			global_unknown
		};
		enum server_config
		{
			host,
			port,
			route,
			server_unknown
		};
		enum route_config
		{
			path,
			route_unknown
		};
		global_config	get_global_key(const std::string & key);
		server_config	get_server_key(const std::string & key);
		route_config	get_route_key(const std::string & key);
		
		JsonObject & 	_global_scope;
		
	public:
						Config(JsonObject & config_object);
						Config(const Config & to_copy);
						~Config();

		
		void			apply(InitiationDispatcher & idis);

		void			print_to_log(void) const;

		Config & 		operator=(const Config & to_assign);
		friend std::ostream & operator<<(std::ostream & os,
											const Config & to_print);
};

#endif
