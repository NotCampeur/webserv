/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:53:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/08/07 18:25:40 by notcampeur       ###   ########.fr       */
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
				JsonArray	* servers = dynamic_cast<JsonArray *>(it->second);
				if (servers == NULL)
					throw;
				JsonArray::value_type::const_iterator ait(servers->value_begin());
				JsonArray::value_type::const_iterator aite(servers->value_end());
				while (ait != aite)
				{
					JsonObject	* server = dynamic_cast<JsonObject *>(*ait);
					if (server == NULL)
						throw;
					JsonObject::value_type::const_iterator oit(server->value_begin());
					JsonObject::value_type::const_iterator oite(server->value_end());
					std::string		port_value("8080");
					ServerConfig	* server_config = new ServerConfig(port_value);
					
					while (oit != oite)
					{
						switch (get_server_key(oit->first))
						{
							case name:
							{
								JsonString	* value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								std::string	name_value = value->value();
								server_config->set_name(name_value);
								break;
							}
							case host:
							{
								JsonString	* value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								std::string	host_value = value->value();
								server_config->set_host(host_value);
								break;
							}
							case port:
							{
								JsonString	* value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								port_value = value->value();
								server_config->set_port(port_value);
								break;
							}
							case max_client_body_size:
							{
								JsonString	* value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								std::string	s_max_client_body_size_value = value->value();
								size_t			max_client_body_size_value(0);
								std::istringstream(s_max_client_body_size_value) >> max_client_body_size_value;
								server_config->set_max_client_body_size(max_client_body_size_value);
								break;
							}
							case auto_index:
							{
								JsonString	* value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								if (value->value() == "true")
									server_config->set_autoindex(true);
								else
									server_config->set_autoindex(false);
								break;
							}
							case root:
							{
								JsonString	* value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								std::string	root_value = value->value();
								server_config->set_root_dir(root_value);
								break;
							}
							case index:
							{
								JsonString	* value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								std::string	index_value = value->value();
								server_config->set_index(index_value);
								break;
							}
							case default_file_dir:
							{
								JsonString	* value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								std::string	default_file_dir_value = value->value();
								server_config->set_default_file_dir(default_file_dir_value);
								break;
							}
							case error_page_path:
							{
								JsonArray	* value = dynamic_cast<JsonArray *>(oit->second);
								if (value == NULL)
									throw;
								JsonObject	* error_page = dynamic_cast<JsonObject *>(*(value->value_begin()));
								if (error_page == NULL)
									throw;
								JsonObject::value_type::const_iterator error_page_oit(error_page->value_begin());
								JsonObject::value_type::const_iterator error_page_oite(error_page->value_end());
								
								while (error_page_oit != error_page_oite)
								{
									JsonString	* error_page_path_value = dynamic_cast<JsonString *>(error_page_oit->second);
									if (value == NULL)
										throw;
									int			page_number(0);
									std::istringstream(error_page_oit->first) >> page_number;
									std::string	error_page_path = error_page_path_value->value();
									
									server_config->add_error_page_path(page_number, error_page_path);
									error_page_oit++;
								}
								break;
							}
							case route:
							{
								JsonArray	* routes = dynamic_cast<JsonArray *>(oit->second);
								if (routes == NULL)
									throw;
								JsonArray::value_type::const_iterator routes_it(routes->value_begin());
								JsonArray::value_type::const_iterator routes_ite(routes->value_end());
								while (routes_it != routes_ite)
								{
									JsonObject	* route = dynamic_cast<JsonObject *>(*routes_it);
									if (route == NULL)
										throw;
									JsonObject::value_type::const_iterator route_it(route->value_begin());
									JsonObject::value_type::const_iterator route_ite(route->value_end());
									RouteConfig	* route_config = new RouteConfig(*server_config);
									while (route_it != route_ite)
									{
										switch (get_route_key(route_it->first))
										{
											case route_path:
											{
												JsonString	* path = dynamic_cast<JsonString *>(route_it->second);
												if (path == NULL)
													throw;
												route_config->set_path(path->value());
												break;
											}
											case route_method:
											{
												JsonString	* method = dynamic_cast<JsonString *>(route_it->second);
												RouteMethod	route_method(NOTHING);
												if (method == NULL)
													throw;
												if (method->value().find("GET") != std::string::npos)
													route_method = GET;
												if (method->value().find("POST") != std::string::npos)
													route_method = static_cast<RouteMethod>(route_method | POST);
												if (method->value().find("DELETE") != std::string::npos)
													route_method = static_cast<RouteMethod>(route_method | DELETE);
												if (method->value().find("ALL") != std::string::npos)
													route_method = ALL;
												route_config->set_accepted_method(route_method);
												break;
											}
											case route_redirection:
											{
												JsonString	* redirection = dynamic_cast<JsonString *>(route_it->second);
												if (redirection == NULL)
													throw;
												route_config->set_redirection(redirection->value());
												break;
											}
											case route_root:
											{
												JsonString	* root = dynamic_cast<JsonString *>(route_it->second);
												if (root == NULL)
													throw;
												route_config->set_root(root->value());
												break;
											}
											case route_auto_index:
											{
												JsonString	* auto_index = dynamic_cast<JsonString *>(route_it->second);
												if (auto_index == NULL)
													throw;
												if (auto_index->value() == "true")
													route_config->set_autoindex(true);
												else
													route_config->set_autoindex(false);
												break;
											}
											case route_default_file_dir:
											{
												JsonString	* default_file_dir = dynamic_cast<JsonString *>(route_it->second);
												if (default_file_dir == NULL)
													throw;
												route_config->set_default_file_dir(default_file_dir->value());
												break;
											}
											case route_cgi:
											{
												JsonString	* cgi = dynamic_cast<JsonString *>(route_it->second);
												if (cgi == NULL)
													throw;
												route_config->set_cgi(cgi->value());
												break;
											}
											case route_upload_path:
											{
												JsonString	* upload_path = dynamic_cast<JsonString *>(route_it->second);
												if (upload_path == NULL)
													throw;
												route_config->set_upload_path(upload_path->value());
												break;
											}
											case route_unknown:
											{
												throw;
											}
										}
										route_it++;
									}
									server_config->add_route(route_config);
									routes_it++;
								}
								break;
							}
							case server_unknown:
							{
								throw;
							}
						}
						oit++;
					}
					const Server	* serv = new Server(server_config);
					idis.add_server_handle(*serv);
					ait++;
				}
				break;
			}
			case global_unknown:
			{
				throw;
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
