/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:53:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/02 00:40:13 by notcampeur       ###   ########.fr       */
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
	else if (key == "ip")
		return ip;
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
	else if (key == "location")
		return location;
	return server_unknown;
}

Config::location_config
Config::get_location_key(const std::string & key)
{
	if (key == "path")
		return location_path;
	else if (key == "accepted_method")
		return location_method;
	else if (key == "redirection")
		return location_redirection;
	else if (key == "root")
		return location_root;
	else if (key == "auto_index")
		return location_auto_index;
	else if (key == "default_file_dir")
		return location_default_file_dir;
	else if (key == "cgi")
		return location_cgi;
	else if (key == "upload_path")
		return location_upload_path;
	return location_unknown;
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
Config::load_server_ip(IJsonValue * server_ip, ServerConfig & server)
{
	JsonString	* value = dynamic_cast<JsonString *>(server_ip);
	if (value == NULL)
		throw Exception("Server's ip must be a \"string\"");
	std::string	ip_value = value->value();
	server.set_ip(ip_value);
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
Config::load_server_location(IJsonValue * server_location, ServerConfig & server)
{
	JsonArray	* locations = dynamic_cast<JsonArray *>(server_location);
	if (locations == NULL)
		throw Exception("Server's locations must be an [array of {objects}]");
	JsonArray::value_type::const_iterator routes_it(locations->value_begin());
	JsonArray::value_type::const_iterator routes_ite(locations->value_end());
	while (routes_it != routes_ite)
	{
		JsonObject	* location = dynamic_cast<JsonObject *>(*routes_it);
		if (location == NULL)
			throw Exception("Server's locations must be an [array of {objects}]");;
		JsonObject::value_type::const_iterator location_it(location->value_begin());
		JsonObject::value_type::const_iterator location_ite(location->value_end());
		LocationConfig	* location_config = new LocationConfig(server);
		while (location_it != location_ite)
		{
			switch (get_location_key(location_it->first))
			{
				case location_path:
					load_location_path(location_it->second, *location_config);
					break;
				case location_method:
					load_location_method(location_it->second, *location_config);
					break;
				case location_redirection:
					load_location_redirection(location_it->second, *location_config);
					break;
				case location_root:
					load_location_root(location_it->second, *location_config);
					break;
				case location_auto_index:
					load_location_auto_index(location_it->second, *location_config);
					break;
				case location_default_file_dir:
					load_location_default_file_dir(location_it->second, *location_config);
					break;
				case location_cgi:
					load_location_cgi(location_it->second, *location_config);
					break;
				case location_upload_path:
					load_location_upload_path(location_it->second, *location_config);
					break;
				case location_unknown:
					throw Exception("Unknown location's key detected");
			}
			location_it++;
		}
		server.add_location(location_config);
		routes_it++;
	}
}

void
Config::load_location_path(IJsonValue * location_path, LocationConfig & location)
{
	JsonString	* path = dynamic_cast<JsonString *>(location_path);
	if (path == NULL)
		throw Exception("Location's path must be a \"string\"");
	location.set_path(path->value());
}

void
Config::load_location_method(IJsonValue * location_method, LocationConfig & location)
{
	JsonString	* method = dynamic_cast<JsonString *>(location_method);
	RouteMethod	accepted_method(NOTHING);
	if (method == NULL)
		throw Exception("Location's accepted_method must be a \"string, string\"");
	if (method->value().find("GET") != std::string::npos)
		accepted_method = GET;
	if (method->value().find("POST") != std::string::npos)
		accepted_method = static_cast<RouteMethod>(accepted_method | POST);
	if (method->value().find("DELETE") != std::string::npos)
		accepted_method = static_cast<RouteMethod>(accepted_method | DELETE);
	if (method->value().find("ALL") != std::string::npos)
		accepted_method = ALL;
	location.set_accepted_method(accepted_method);
}

void
Config::load_location_redirection(IJsonValue * location_redirection, LocationConfig & location)
{
	JsonString	* redirection = dynamic_cast<JsonString *>(location_redirection);
	if (redirection == NULL)
		throw Exception("Location's redirection must be a \"string\"");
	location.set_redirection(redirection->value());
}

void
Config::load_location_root(IJsonValue * location_root, LocationConfig & location)
{
	JsonString	* root = dynamic_cast<JsonString *>(location_root);
	if (root == NULL)
		throw Exception("Location's root must be a \"string\"");
	location.set_root(root->value());
}

void
Config::load_location_auto_index(IJsonValue * location_auto_index, LocationConfig & location)
{
	JsonString	* auto_index = dynamic_cast<JsonString *>(location_auto_index);
	if (auto_index == NULL)
		throw Exception("Location's auto_index must be a \"string\"");
	if (auto_index->value() == "true")
		location.set_autoindex(true);
	else
		location.set_autoindex(false);
}

void
Config::load_location_default_file_dir(IJsonValue * location_default_file_dir, LocationConfig & location)
{
	JsonString	* default_file_dir = dynamic_cast<JsonString *>(location_default_file_dir);
	if (default_file_dir == NULL)
		throw Exception("Location's default_file_dir must be a \"string\"");
	location.set_default_file_dir(default_file_dir->value());
}

void
Config::load_location_cgi(IJsonValue * location_cgi, LocationConfig & location)
{
	JsonArray	* cgi_array = dynamic_cast<JsonArray *>(location_cgi);
	if (cgi_array == NULL)
		throw Exception("Location's cgi must be an [array of {objects}]");
	JsonObject	* cgi_object = dynamic_cast<JsonObject *>(*(cgi_array->value_begin()));
	if (cgi_object == NULL)
		throw Exception("Location's cgi must be an [array of {objects}]");
	JsonObject::value_type::const_iterator cgi_object_it(cgi_object->value_begin());
	JsonObject::value_type::const_iterator cgi_object_ite(cgi_object->value_end());
	while (cgi_object_it != cgi_object_ite)
	{
		JsonString	* cgi_path = dynamic_cast<JsonString *>(cgi_object_it->second);
		if (cgi_path == NULL)
			throw Exception("Cgi_path's values must be \"strings\"");
		location.add_cgi(cgi_object_it->first, cgi_path->value());
		cgi_object_it++;
	}
}

void
Config::load_location_upload_path(IJsonValue * location_upload_path, LocationConfig & location)
{
	JsonString	* upload_path = dynamic_cast<JsonString *>(location_upload_path);
	if (upload_path == NULL)
		throw Exception("Location's upload_path must be a \"string\"");
	location.set_upload_path(upload_path->value());
}

ServerConfig *
Config::load_server_config(IJsonValue * server_object)
{
	JsonObject		* server = dynamic_cast<JsonObject *>(server_object);
	if (server == NULL)
		throw Exception("Server must be an [array of {objects}]");
	ServerConfig	* server_config = new ServerConfig();
	JsonObject::value_type::const_iterator ite(server->value_end());
	
	for (JsonObject::value_type::const_iterator it(server->value_begin())
		; it != ite; it++)
	{
		switch (get_server_key(it->first))
		{
			case name:
				load_server_name(it->second, *server_config);
				break;
			case ip:
				load_server_ip(it->second, *server_config);
				break;
			case port:
				load_server_port(it->second, *server_config);
				break;
			case max_client_body_size:
				load_server_max_client_body_size(it->second, *server_config);
				break;
			case auto_index:
				load_server_auto_index(it->second, *server_config);
				break;
			case root:
				load_server_root(it->second, *server_config);
				break;
			case index:
				load_server_index(it->second, *server_config);
				break;
			case default_file_dir:
				load_server_default_file_dir(it->second, *server_config);
				break;
			case error_page_path:
				load_server_error_page_path(it->second, *server_config);
				break;
			case location:
				load_server_location(it->second, *server_config);
				break;
			case server_unknown:
				throw Exception("Unknown server's key detected");
		}
	}
	return server_config;
}

void
Config::load_servers_config(IJsonValue * server_array)
{
	JsonArray *	servers = dynamic_cast<JsonArray *>(server_array);
	if (servers == NULL)
		throw Exception("Server must be an [array of {objects}]");
	JsonArray::value_type::const_iterator ait(servers->value_begin());
	JsonArray::value_type::const_iterator aite(servers->value_end());
	std::vector<ServerConfig *>	servers_config;
	std::vector<Server *>		server_list;
	bool						is_same_server(false);
	
	while (ait != aite)
	{
		servers_config.push_back(load_server_config(*ait));
		ait++;
	}
	for (size_t i(0); i < servers_config.size(); i++)
	{
		for (size_t j(0); j < server_list.size(); j++)
		{
			Server::config_type::const_iterator it(server_list[j]->get_server_config().begin());
			if (servers_config[i]->ip() == it->second.ip()
			&& servers_config[i]->port() == it->second.port())
			{
				server_list[j]->add_server_config(*servers_config[i]);
				Logger(LOG_FILE, basic_type, debug_lvl) << "Multiple server configuration added for the same Host : " << it->second.ip();
				is_same_server = true;
				break;
			}
		}
		if (is_same_server == false)
			server_list.push_back(new Server(servers_config[i]));
		is_same_server = false;
	}
	for (size_t i(0); i < server_list.size(); i++)
		InitiationDispatcher::get_instance().add_server_handle(*server_list[i]);
}

void
Config::apply()
{
	JsonObject::value_type::const_iterator it(_global_scope.value_begin());
	JsonObject::value_type::const_iterator ite(_global_scope.value_end());

	while (it != ite)
	{
		switch (get_global_key(it->first))
		{
			case server:
			{
				load_servers_config(it->second);
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
