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
		std::map<int, std::string>			_error_pages;
		size_t								_max_client_body_size;
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
		std::map<int, std::string>			error_pages(void) const;
		size_t								max_client_body_size(void) const;
		HTTPMethod							accepted_method(void) const;
		std::pair<int, std::string>			redirection(void) const;
		std::string							root(void) const;
		bool								is_autoindex_on(void) const;
		std::string							default_file_dir(void) const;
		std::map<std::string, std::string>	cgi(void) const;
		std::string							upload_path(void) const;

		//Setters
		void	set_error_pages(std::map<int, std::string> error_pages);
		void	add_error_pages(int error, const std::string & page_path);
		void	set_max_client_body_size(size_t max_size);
		void	set_accepted_method(const HTTPMethod & accepted_method);
		void	set_redirection(std::pair<int, std::string> & redirection);
		void	set_root(const std::string & root_path);
		void	set_is_autoindex_on(bool is_autoindex_on);
		void	set_default_file_dir(const std::string & default_file_dir);
		void	set_cgi(const std::map<std::string, std::string> & cgi);
		void	set_upload_path(const std::string & upload_path);

		void	set_root(std::string const &root_dir);
		void	set_index(std::string const &index);
		void	set_autoindex(bool is_autoindex_on);
		void	set_default_file_dir(std::string const &default_file_dir);
		void	set_accepted_method(HTTPMethod value);

		//Operators
		RequestConfig	&operator=(const RequestConfig & to_assign);
		RequestConfig	&operator=(const LocationConfig & to_assign);
		RequestConfig	&operator=(const ServerConfig & to_assign);
};

#endif
