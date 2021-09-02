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

class RequestConfig
{
	private:
		std::string							_name;
		std::string							_ip;
		std::string							_port;
		std::map<int, std::string>			_error_pages;
		size_t								_max_client_body_size;
		std::vector<LocationConfig *>		_locations;
		HTTPMethod							_accepted_method;
		std::pair<int, std::string>			_redirection;
		std::string							_root;
		bool								_is_autoindex_on;
		std::string							_default_file_dir;
		std::map<std::string, std::string>	_cgi;
		std::string							_upload_path;

	public:
		RequestConfig();
		RequestConfig(const RequestConfig & to_copy);
		~RequestConfig();

		//Getters
		std::string							name(void) const;
		std::string							ip(void) const;
		std::string							port(void) const;
		std::map<int, std::string>			error_pages(void) const;
		size_t								max_client_body_size(void) const;
		const std::vector<LocationConfig *> &	locations(void) const;
		HTTPMethod							accepted_method(void) const;
		std::pair<int, std::string>			redirection(void) const;
		std::string							root(void) const;
		bool								is_autoindex_on(void) const;
		std::string							default_file_dir(void) const;
		std::map<std::string, std::string>	cgi(void) const;
		std::string							upload_path(void) const;

		//Operators
		RequestConfig	&operator=(const RequestConfig & to_assign);
		RequestConfig	&operator=(const LocationConfig & to_assign);
		RequestConfig	&operator=(const ServerConfig & to_assign);
};

#endif
