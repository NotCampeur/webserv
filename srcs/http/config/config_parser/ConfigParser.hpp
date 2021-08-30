/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:28:12 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/29 19:05:56 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONFIG_PARSER_HPP
# define WEBSERV_CONFIG_PARSER_HPP

# include "webserv.hpp"
# include "Config.hpp"

class ConfigParser
{
		std::string		_path_to_file;
		std::string		_raw_data;
		Config			_configuration;

		//	Simply open the config file and load the data to prepare the parsing.
		void		load();
		
	public:
		ConfigParser(std::string path_to_file = "ressources/config/webserv.conf");
		~ConfigParser();

		//	Return the configuration set in accordance to the json config file.
		Config	&configuration(void);
		
		class UnableToOpenFile : public std::exception
		{
				std::string	_msg;
				
			public:
				UnableToOpenFile() throw();
				~UnableToOpenFile() throw();
				const char * what(void) const throw();
		};
};

#endif
