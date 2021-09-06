/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:35:39 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/06 18:46:19 by notcampeur       ###   ########.fr       */
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
			ip,
			port,
			error_page_path,
			max_client_body_size,
			location,
			server_unknown
		};
		enum location_config
		{
			location_path,
			location_method,
			location_redirection,
			location_root,
			location_auto_index,
			location_default_file_dir,
			location_cgi,
			location_upload_path,
			location_unknown
		};
		global_config	get_global_key(const std::string & key);
		server_config	get_server_key(const std::string & key);
		location_config	get_location_key(const std::string & key);
		
		JsonObject & 	_global_scope;
		
		void			load_servers_config(IJsonValue * server_array);
		ServerConfig	*load_server_config(IJsonValue * server_object);

		void			load_server_name(IJsonValue * server_name, ServerConfig & server);
		void			load_server_ip(IJsonValue * server_ip, ServerConfig & server);
		void			load_server_port(IJsonValue * server_port, ServerConfig & server);
		void			load_server_error_page_path(IJsonValue * server_error_page_path, ServerConfig & server);
		void			load_server_max_client_body_size(IJsonValue * server_max_client_body_size, ServerConfig & server);
		void			load_server_location(IJsonValue * server_location, ServerConfig & server);
		
		void			load_location_path(IJsonValue * location_path, LocationConfig & location);
		void			load_location_method(IJsonValue * location_method, LocationConfig & location);
		void			load_location_redirection(IJsonValue * location_redirection, LocationConfig & location);
		void			load_location_root(IJsonValue * location_root, LocationConfig & location);
		void			load_location_auto_index(IJsonValue * location_auto_index, LocationConfig & location);
		void			load_location_default_file_dir(IJsonValue * location_default_file_dir, LocationConfig & location);
		void			load_location_cgi(IJsonValue * location_cgi, LocationConfig & location);
		void			load_location_upload_path(IJsonValue * location_upload_path, LocationConfig & location);

		void			remove_items(std::vector<ServerConfig *> &vec);
		void			remove_items(std::vector<Server *> &vec);
		
	public:
						Config(JsonObject & config_object);
						Config(const Config & to_copy);
						~Config();

		
		void			apply();

		void			print_to_log(void) const;

		Config & 		operator=(const Config & to_assign);
		friend std::ostream & operator<<(std::ostream & os,
											const Config & to_print);
};

#endif
