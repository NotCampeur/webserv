/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:35:39 by ldutriez          #+#    #+#             */
/*   Updated: 2021/08/26 12:28:52 by notcampeur       ###   ########.fr       */
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
class RouteConfig;

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
			route_path,
			route_method,
			route_redirection,
			route_root,
			route_auto_index,
			route_default_file_dir,
			route_cgi,
			route_upload_path,
			route_unknown
		};
		global_config	get_global_key(const std::string & key);
		server_config	get_server_key(const std::string & key);
		route_config	get_route_key(const std::string & key);
		
		JsonObject & 	_global_scope;
		
		void			load_servers_config(IJsonValue * server_array);
		ServerConfig	*load_server_config(IJsonValue * server_object);

		void			load_server_name(IJsonValue * server_name, ServerConfig & server);
		void			load_server_host(IJsonValue * server_host, ServerConfig & server);
		void			load_server_port(IJsonValue * server_port, ServerConfig & server);
		void			load_server_max_client_body_size(IJsonValue * server_max_client_body_size, ServerConfig & server);
		void			load_server_auto_index(IJsonValue * server_auto_index, ServerConfig & server);
		void			load_server_root(IJsonValue * server_root, ServerConfig & server);
		void			load_server_index(IJsonValue * server_index, ServerConfig & server);
		void			load_server_default_file_dir(IJsonValue * server_default_file_dir, ServerConfig & server);
		void			load_server_error_page_path(IJsonValue * server_error_page_path, ServerConfig & server);
		void			load_server_route(IJsonValue * server_route, ServerConfig & server);
		
		void			load_route_path(IJsonValue * route_path, RouteConfig & route);
		void			load_route_method(IJsonValue * route_method, RouteConfig & route);
		void			load_route_redirection(IJsonValue * route_redirection, RouteConfig & route);
		void			load_route_root(IJsonValue * route_root, RouteConfig & route);
		void			load_route_auto_index(IJsonValue * route_auto_index, RouteConfig & route);
		void			load_route_default_file_dir(IJsonValue * route_default_file_dir, RouteConfig & route);
		void			load_route_cgi(IJsonValue * route_cgi, RouteConfig & route);
		void			load_route_upload_path(IJsonValue * route_upload_path, RouteConfig & route);

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
