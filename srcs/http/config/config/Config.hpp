/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:35:39 by ldutriez          #+#    #+#             */
/*   Updated: 2021/08/05 17:48:47 by notcampeur       ###   ########.fr       */
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
			name,
			host,
			port,
			max_client_body_size,
			auto_index,
			root,
			index,
			default_file_dir,
			error_page_path,
			route,
			server_unknown
		};
		enum route_config
		{
			path,
			accepted_method,
			redirection,
			root,
			auto_index,
			default_file_dir,
			cgi,
			upload_path,
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
