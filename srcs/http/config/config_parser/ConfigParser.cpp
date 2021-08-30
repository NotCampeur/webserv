/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:49:26 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/24 19:06:49 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(std::string path_to_file)
: _path_to_file(path_to_file), _raw_data(), _configuration()
{
	load();
}

ConfigParser::~ConfigParser()
{}

void
ConfigParser::load(void)
{
	std::ifstream	file(_path_to_file);
	std::string		tmp;
	
	if (file.is_open() == false)
		throw UnableToOpenFile();
	while (file.peek() != EOF)
	{
		file >> tmp;
		_raw_data += tmp;
	}
	file.close();
	Logger(LOG_FILE, basic_type, debug_lvl) << "Config file has been loaded up : \n" << _raw_data;
}

Config &
ConfigParser::configuration(void)
{
	return _configuration;
}

ConfigParser::UnableToOpenFile::UnableToOpenFile() throw()
: _msg("Unable to open the configuration file : ")
{
	_msg += strerror(errno);
}

ConfigParser::UnableToOpenFile::~UnableToOpenFile() throw()
{}

const char *
ConfigParser::UnableToOpenFile::what() const throw()
{
	return _msg.c_str();
}
