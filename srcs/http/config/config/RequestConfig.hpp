/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestConfig.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:43:58 by notcampeur        #+#    #+#             */
/*   Updated: 2021/09/02 04:20:23 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_REQUEST_CONFIG_HPP
# define WEBSERVER_REQUEST_CONFIG_HPP

# include <string>
# include "Singleton.hpp"
# include <LocationConfig.hpp>
class ServerConfig;
class LocationConfig;

class RequestConfig
{
	private:
		const std::string							&_name;
		const std::string							&_ip;
		const std::string							&_port;
		const std::map<int, std::string>			&_error_pages;
		const size_t								_max_client_body_size;
		// const std::vector<LocationConfig *>			&_locations;
		const HTTPMethod							&_accepted_method;
		const std::pair<int, std::string>			&_redirection;
		const std::string							&_root;
		const bool									_is_autoindex_on;
		const std::string							&_default_file_dir;
		const std::map<std::string, std::string>	&_cgi;
		const std::string							&_upload_path;
		const std::string							&_path;

	public:
		RequestConfig(const ServerConfig & serv_conf, const LocationConfig & loc_conf);
		~RequestConfig();

		//Getters
		const std::string							& name(void) const;
		const std::string							& ip(void) const;
		const std::string							& port(void) const;
		const std::map<int, std::string>			& error_pages(void) const;
		size_t										max_client_body_size(void) const;
		// const const std::vector<LocationConfig *>	& locations(void) const;
		const HTTPMethod							& accepted_method(void) const;
		const std::pair<int, std::string>			& redirection(void) const;
		const std::string							& root(void) const;
		bool										is_autoindex_on(void) const;
		const std::string							& default_file_dir(void) const;
		const std::map<std::string, std::string>	& cgi(void) const;
		const std::string							& upload_path(void) const;
		const std::string							& location_path(void) const;

		//Operators
		// RequestConfig	&operator=(const LocationConfig & to_assign);
		// RequestConfig	&operator=(const ServerConfig & to_assign);

		private:
			RequestConfig();
			RequestConfig(const RequestConfig & to_copy);
			RequestConfig	&operator=(const RequestConfig & to_assign);

};

#endif
