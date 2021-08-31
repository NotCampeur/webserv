/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ValidatorConfig.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:43:58 by notcampeur        #+#    #+#             */
/*   Updated: 2021/08/31 22:09:28 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_VALIDATOR_CONFIG_HPP
# define WEBSERVER_VALIDATOR_CONFIG_HPP

# include <string>
# include "Singleton.hpp"
# include <LocationConfig.hpp>

class ValidatorConfig : public Singleton<ValidatorConfig>
{
	private:
		std::string					_root_dir;
		std::string					_index;
		bool						_is_autoindex_on;
		std::string					_default_file_dir;
		RouteMethod					_accepted_method;

	public:
		ValidatorConfig();
		ValidatorConfig(const ValidatorConfig & to_copy);
		~ValidatorConfig();

		//Getters
		std::string					root_dir() const;
		std::string					index() const;
		bool						is_autoindex_on() const;
		std::string					default_file_dir() const;
		RouteMethod					accepted_method() const;

		//Setters
		void						set_root_dir(std::string const &root_dir);
		void						set_index(std::string const &index);
		void						set_autoindex(bool is_autoindex_on);
		void						set_default_file_dir(std::string const &default_file_dir);
		void						set_accepted_method(RouteMethod value);

		//Operators
		ValidatorConfig				&operator=(const ValidatorConfig & to_assign);
		ValidatorConfig				&operator=(const LocationConfig & to_assign);
		ValidatorConfig				&operator=(const ServerConfig & to_assign);
};

#endif
