/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:53:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/13 18:08:27 by notcampeur       ###   ########.fr       */
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
{}

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
	if (key == "host")
		return host;
	else if (key == "port")
		return port;
	else if (key == "route")
		return route;
	return server_unknown;
}

Config::route_config
Config::get_route_key(const std::string & key)
{
	if (key == "path")
		return path;
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
				JsonArray	*servers = dynamic_cast<JsonArray *>(it->second);
				if (servers == NULL)
					throw;
				JsonArray::value_type::const_iterator ait(servers->value_begin());
				JsonArray::value_type::const_iterator aite(servers->value_end());
				while (ait != aite)
				{
					JsonObject	*server = dynamic_cast<JsonObject *>(*ait);
					if (server == NULL)
						throw;
					JsonObject::value_type::const_iterator oit(server->value_begin());
					JsonObject::value_type::const_iterator oite(server->value_end());
					std::string	host_value("127.0.0.1");
					std::string	port_value("8080");
					
					while (oit != oite)
					{
						switch (get_server_key(oit->first))
						{
							case host:
							{
								JsonString	*value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								host_value = value->value();
								break;
							}
							case port:
							{
								JsonString	*value = dynamic_cast<JsonString *>(oit->second);
								if (value == NULL)
									throw;
								port_value = value->value();
								break;
							}
							case route:
							{
								break;
							}
							case server_unknown:
							{
								throw;
							}
						}
						oit++;
					}
					const Server *serv = new Server(atoi(port_value.c_str()), inet_addr(host_value.c_str()));
					idis.add_handle(*serv);
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
