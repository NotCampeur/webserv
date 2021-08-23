/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:53:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/08/23 20:54:05 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(JsonObject & config_object)
: _global_scope(config_object)
{}

Config::Config(const Config & to_copy)
: _global_scope(to_copy._global_scope)
{}

Config::~Config()
{
	delete &_global_scope;
}

Config::global_config
Config::get_global_key(const std::string & key)
{
	if (key == "server")
		return server;
	return global_unknown;
}

Config::server_config
Config::get_server_key(const std::string & key)
{
	if (key == "name")
		return name;
	else if (key == "host")
		return host;
	else if (key == "port")
		return port;
	else if (key == "max_client_body_size")
		return max_client_body_size;
	else if (key == "auto_index")
		return auto_index;
	else if (key == "root")
		return root;
	else if (key == "index")
		return index;
	else if (key == "default_file_dir")
		return default_file_dir;
	else if (key == "error_page_path")
		return error_page_path;
	else if (key == "route")
		return route;
	return server_unknown;
}

Config::route_config
Config::get_route_key(const std::string & key)
{
	if (key == "path")
		return route_path;
	else if (key == "accepted_method")
		return route_method;
	else if (key == "redirection")
		return route_redirection;
	else if (key == "root")
		return route_root;
	else if (key == "auto_index")
		return route_auto_index;
	else if (key == "default_file_dir")
		return route_default_file_dir;
	else if (key == "cgi")
		return route_cgi;
	else if (key == "upload_path")
		return route_upload_path;
	return route_unknown;
}

void
Config::load_server_name(IJsonValue * server_name, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_name);
	if (value == NULL)
		throw Exception("Server's name must be a \"string\"");
	std::string	name_value = value->value();
	server.set_name(name_value);
}

void
Config::load_server_host(IJsonValue * server_host, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_host);
	if (value == NULL)
		throw Exception("Server's host must be a \"string\"");
	std::string	host_value = value->value();
	server.set_host(host_value);
}

void
Config::load_server_port(IJsonValue * server_port, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_port);
	if (value == NULL)
		throw Exception("Server's port must be a \"string\"");
	std::string port_value = value->value();
	server.set_port(port_value);
}

void
Config::load_server_max_client_body_size(IJsonValue * server_max_client_body_size, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_max_client_body_size);
	if (value == NULL)
		throw Exception("Server's max_client_body_size must be a \"string\"");
	std::string	s_max_client_body_size_value = value->value();
	size_t			max_client_body_size_value(0);
	std::istringstream(s_max_client_body_size_value) >> max_client_body_size_value;
	server.set_max_client_body_size(max_client_body_size_value);
}

void
Config::load_server_auto_index(IJsonValue * server_auto_index, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_auto_index);
	if (value == NULL)
		throw Exception("Server's auto_index must be a \"string\"");
	if (value->value() == "true")
		server.set_autoindex(true);
	else
		server.set_autoindex(false);
}

void
Config::load_server_root(IJsonValue * server_root, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_root);
	if (value == NULL)
		throw Exception("Server's root must be a \"string\"");
	std::string	root_value = value->value();
	server.set_root_dir(root_value);
}

void
Config::load_server_index(IJsonValue * server_index, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_index);
	if (value == NULL)
		throw Exception("Server's index must be a \"string\"");
	std::string	index_value = value->value();
	server.set_index(index_value);
}

void
Config::load_server_default_file_dir(IJsonValue * server_default_file_dir, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_default_file_dir);
	if (value == NULL)
		throw Exception("Server's default_file_dir must be a \"string\"");
	std::string	default_file_dir_value = value->value();
	server.set_default_file_dir(default_file_dir_value);
}

void
Config::load_server_error_page_path(IJsonValue * server_error_page_path, ServerConfig & server)
{
	JsonArray	* value = dynamic_cast<JsonArray *>(server_error_page_path);
	if (value == NULL)
		throw Exception("Server's error_page_path must be an [array of {objects}]");
	JsonObject	* error_page = dynamic_cast<JsonObject *>(*(value->value_begin()));
	if (error_page == NULL)
		throw Exception("Server's error_page_path must be an [array of {objects}]");
	JsonObject::value_type::const_iterator error_page_oit(error_page->value_begin());
	JsonObject::value_type::const_iterator error_page_oite(error_page->value_end());
	
	while (error_page_oit != error_page_oite)
	{
		JsonString	* error_page_path_value = dynamic_cast<JsonString *>(error_page_oit->second);
		if (value == NULL)
			throw Exception("Error_page_path's values must be \"strings\"");
		int			page_number(0);
		std::istringstream(error_page_oit->first) >> page_number;
		std::string	error_page_path = error_page_path_value->value();
		
		server.add_error_page_path(page_number, error_page_path);
		error_page_oit++;
	}
}

void
Config::load_server_route(IJsonValue * server_route, ServerConfig & server)
{
	JsonArray	* routes = dynamic_cast<JsonArray *>(server_route);
	if (routes == NULL)
		throw Exception("Server's routes must be an [array of {objects}]");
	JsonArray::value_type::const_iterator routes_it(routes->value_begin());
	JsonArray::value_type::const_iterator routes_ite(routes->value_end());
	while (routes_it != routes_ite)
	{
		JsonObject	* route = dynamic_cast<JsonObject *>(*routes_it);
		if (route == NULL)
			throw Exception("Server's routes must be an [array of {objects}]");;
		JsonObject::value_type::const_iterator route_it(route->value_begin());
		JsonObject::value_type::const_iterator route_ite(route->value_end());
		RouteConfig	* route_config = new RouteConfig(server);
		while (route_it != route_ite)
		{
			switch (get_route_key(route_it->first))
			{
				case route_path:
					load_route_path(route_it->second, *route_config);
					break;
				case route_method:
					load_route_method(route_it->second, *route_config);
					break;
				case route_redirection:
					load_route_redirection(route_it->second, *route_config);
					break;
				case route_root:
					load_route_root(route_it->second, *route_config);
					break;
				case route_auto_index:
					load_route_auto_index(route_it->second, *route_config);
					break;
				case route_default_file_dir:
					load_route_default_file_dir(route_it->second, *route_config);
					break;
				case route_cgi:
					load_route_cgi(route_it->second, *route_config);
					break;
				case route_upload_path:
					load_route_upload_path(route_it->second, *route_config);
					break;
				case route_unknown:
					throw Exception("Unknown route's key detected");
			}
			route_it++;
		}
		server.add_route(route_config);
		routes_it++;
	}
}

void
Config::load_route_path(IJsonValue * route_path, RouteConfig & route)
{
	JsonString	* path = dynamic_cast<JsonString *>(route_path);
	if (path == NULL)
		throw Exception("Route's path must be a \"string\"");
	route.set_path(path->value());
}

void
Config::load_route_method(IJsonValue * route_method, RouteConfig & route)
{
	JsonString	* method = dynamic_cast<JsonString *>(route_method);
	RouteMethod	accepted_method(NOTHING);
	if (method == NULL)
		throw Exception("Route's accepted_method must be a \"string, string\"");
	if (method->value().find("GET") != std::string::npos)
		accepted_method = GET;
	if (method->value().find("POST") != std::string::npos)
		accepted_method = static_cast<RouteMethod>(accepted_method | POST);
	if (method->value().find("DELETE") != std::string::npos)
		accepted_method = static_cast<RouteMethod>(accepted_method | DELETE);
	if (method->value().find("ALL") != std::string::npos)
		accepted_method = ALL;
	route.set_accepted_method(accepted_method);
}

void
Config::load_route_redirection(IJsonValue * route_redirection, RouteConfig & route)
{
	JsonString	* redirection = dynamic_cast<JsonString *>(route_redirection);
	if (redirection == NULL)
		throw Exception("Route's redirection must be a \"string\"");
	route.set_redirection(redirection->value());
}

void
Config::load_route_root(IJsonValue * route_root, RouteConfig & route)
{
	JsonString	* root = dynamic_cast<JsonString *>(route_root);
	if (root == NULL)
		throw Exception("Route's root must be a \"string\"");
	route.set_root(root->value());
}

void
Config::load_route_auto_index(IJsonValue * route_auto_index, RouteConfig & route)
{
	JsonString	* auto_index = dynamic_cast<JsonString *>(route_auto_index);
	if (auto_index == NULL)
		throw Exception("Route's auto_index must be a \"string\"");
	if (auto_index->value() == "true")
		route.set_autoindex(true);
	else
		route.set_autoindex(false);
}

void
Config::load_route_default_file_dir(IJsonValue * route_default_file_dir, RouteConfig & route)
{
	JsonString	* default_file_dir = dynamic_cast<JsonString *>(route_default_file_dir);
	if (default_file_dir == NULL)
		throw Exception("Route's default_file_dir must be a \"string\"");
	route.set_default_file_dir(default_file_dir->value());
}

void
Config::load_route_cgi(IJsonValue * route_cgi, RouteConfig & route)
{
	JsonArray	* cgi_array = dynamic_cast<JsonArray *>(route_cgi);
	if (cgi_array == NULL)
		throw Exception("Route's cgi must be an [array of {objects}]");
	JsonObject	* cgi_object = dynamic_cast<JsonObject *>(*(cgi_array->value_begin()));
	if (cgi_object == NULL)
		throw Exception("Route's cgi must be an [array of {objects}]");
	JsonObject::value_type::const_iterator cgi_object_it(cgi_object->value_begin());
	JsonObject::value_type::const_iterator cgi_object_ite(cgi_object->value_end());
	while (cgi_object_it != cgi_object_ite)
	{
		JsonString	* cgi_path = dynamic_cast<JsonString *>(cgi_object_it->second);
		if (cgi_path == NULL)
			throw Exception("Cgi_path's values must be \"strings\"");
		route.add_cgi(cgi_object_it->first, cgi_path->value());
		cgi_object_it++;
	}
}

void
Config::load_route_upload_path(IJsonValue * route_upload_path, RouteConfig & route)
{
	JsonString	* upload_path = dynamic_cast<JsonString *>(route_upload_path);
	if (upload_path == NULL)
		throw Exception("Route's upload_path must be a \"string\"");
	route.set_upload_path(upload_path->value());
}

void
Config::load_server_config(IJsonValue * server_array, InitiationDispatcher & idis)
{
	JsonArray	* servers = dynamic_cast<JsonArray *>(server_array);
	if (servers == NULL)
		throw Exception("Server must be an [array of {objects}]");
	JsonArray::value_type::const_iterator ait(servers->value_begin());
	JsonArray::value_type::const_iterator aite(servers->value_end());
	while (ait != aite)
	{
		JsonObject	* server = dynamic_cast<JsonObject *>(*ait);
		if (server == NULL)
			throw Exception("Server must be an [array of {objects}]");
		JsonObject::value_type::const_iterator oit(server->value_begin());
		JsonObject::value_type::const_iterator oite(server->value_end());
		std::string		port_value("8080");
		ServerConfig	* server_config = new ServerConfig(port_value);
		while (oit != oite)
		{
			switch (get_server_key(oit->first))
			{
				case name:
					load_server_name(oit->second, *server_config);
					break;
				case host:
					load_server_host(oit->second, *server_config);
					break;
				case port:
					load_server_port(oit->second, *server_config);
					break;
				case max_client_body_size:
					load_server_max_client_body_size(oit->second, *server_config);
					break;
				case auto_index:
					load_server_auto_index(oit->second, *server_config);
					break;
				case root:
					load_server_root(oit->second, *server_config);
					break;
				case index:
					load_server_index(oit->second, *server_config);
					break;
				case default_file_dir:
					load_server_default_file_dir(oit->second, *server_config);
					break;
				case error_page_path:
					load_server_error_page_path(oit->second, *server_config);
					break;
				case route:
					load_server_route(oit->second, *server_config);
					break;
				case server_unknown:
					throw Exception("Unknown server's key detected");
			}
			oit++;
		}
		const Server	* serv = new Server(server_config);
		idis.add_server_handle(*serv);
		ait++;
	}
}

void
Config::apply(InitiationDispatcher & idis)
{
	JsonObject::value_type::const_iterator it(_global_scope.value_begin());
	JsonObject::value_type::const_iterator ite(_global_scope.value_end());

	while (it != ite)
	{
		switch (get_global_key(it->first))
		{
			case server:
			{
				load_server_config(it->second, idis);
				break;
			}
			case global_unknown:
			{
				throw Exception("Unknown global's key detected");
			}
		}
		it++;
	}
}

void
Config::print_to_log(void) const
{
	std::string buffer("Config content :\n");

	_global_scope.print_to_buffer(1, buffer);
	Logger(LOG_FILE, basic_type, debug_lvl) << buffer;
}

Config & Config::operator=(const Config & to_assign)
{
	if (this != &to_assign)
		_global_scope = to_assign._global_scope;
	return *this;
}

std::ostream &
operator<<(std::ostream & os, const Config & to_print)
{
	os << "Config loaded :\n";
	os << to_print._global_scope;
	return os;
}
