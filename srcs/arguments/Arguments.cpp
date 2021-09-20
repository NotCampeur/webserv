#include "Arguments.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "libft_string.hpp"
#include "Logger.hpp"
#include "webserv_param.hpp"
#include "Exception.hpp"
#include <sys/stat.h>

Arguments::Arguments(void)
: Singleton()
, _config_path()
, _log_file()
, _is_log_importance_set(false)
, _is_help_set(false)
{}

Arguments::~Arguments(void)
{}

void
Arguments::print_help(void) const
{
	std::cout << "Usage: webserv [config_path] [options]\n\n"
	<< "    Webserv is a program that allow you to run a web server\n"
	<< "        using the protocol HTTP/1.1\n\n"
	<< "config_path is the path to the configuration file.\n\n"
	<< "Options:\n"
	<< "    --log_file=FILE.log\n"
	<< "                file where the log will be written\n"
	<< "                    the file will be created if not exist.\n\n"
	<< "    --log_importance=FLAGS\n"
	<< "                Importance accepted for the log entry\n"
	<< "                it can be one of the following:\n"
	<< "                    debug, minor, major, error, all (all can only be writen alone)\n"
	<< "                note that you can combine importance level by doing this :\n"
	<< "                    --log_importance=major,minor,error\n"
	<< "                On the above exemple, only the :\n"
	<< "                    minor, major or error entries will be print.\n\n"
	<< "    --help      print this help message.\n\n"
	<< "Good to know:\n"
	<< "    The default value for theses optional params are :\n"
	<< "                config_path = ./ressources/config/webserv.conf\n"
	<< "                log_file = ./webserv.log\n"
	<< "                log_importance = error or major\n\n"
	<< "    The webserv will try to load the configuration file from the path given in the command line.\n"
	<< "    If the file is not found, it will throw an error.\n"
	<< "    If you don't know where to start check the default configuration file" << std::endl;
	exit(EXIT_SUCCESS);
}

bool
Arguments::set_config_path(const std::string& config_path)
{
	struct stat		sb;

	if (_config_path.empty() == false)
	{
		std::cerr << "Error: Multiple configuration files" << std::endl;
		return false;
	}
	if (config_path.find(".conf\0") != config_path.size() - 5)
	{
		std::cerr << "Error: Config file must be a .conf file" << std::endl;
		return false;
	}
	if (stat(config_path.c_str(), &sb) != 0 || S_ISREG(sb.st_mode) == false)
	{
		std::cerr << "Error: Config File must be an existing file" << std::endl;
		return false;
	}
	_config_path = config_path;
	return true;
}

bool
Arguments::set_log_file(const std::string& log_file)
{
	struct stat		sb;
	
	if (_log_file.empty() == false)
	{
		std::cerr << "Error: Multiple log files" << std::endl;
		return false;
	}
	_log_file = log_file.substr(11);
	if (_log_file.find(".log\0") != _log_file.size() - 4)
	{
		std::cerr << "Error: Log file must be a .log file" << std::endl;
		return false;
	}
	if (stat(_log_file.c_str(), &sb) == 0 && S_ISREG(sb.st_mode) == false)
	{
		std::cerr << "Error: Log file is not a regular one" << std::endl;
		return false;
	}
	return true;
}

bool
Arguments::set_log_importance(const std::string importance_level)
{
	if (_is_log_importance_set == true)
	{
		std::cerr << "Error: Multiple log importance levels" << std::endl;
		return false;
	}
	_is_log_importance_set = true;

	std::vector<std::string>	importance(ft_split(importance_level.substr(17), ","));
	log_importance_level		accepted_importance(none_lvl);

	if (importance.size() == 1 && importance[0] == "all")
	{
		Logger::accept_importance(all_lvl);
		return true;
	}
	for (std::vector<std::string>::iterator it = importance.begin()
		; it != importance.end()
		; ++it)
	{
		if (*it == "debug")
			if ((accepted_importance & debug_lvl) == 0)
				accepted_importance = accepted_importance | debug_lvl;
			else
			{
				std::cerr << "Error: Duplicate log importance level: debug" << std::endl;
				return false;
			}
		else if (*it == "minor")
			if ((accepted_importance & minor_lvl) == 0)
				accepted_importance = accepted_importance | minor_lvl;
			else
			{
				std::cerr << "Error: Duplicate log importance level: minor" << std::endl;
				return false;
			}
		else if (*it == "major")
			if ((accepted_importance & major_lvl) == 0)
				accepted_importance = accepted_importance | major_lvl;
			else
			{
				std::cerr << "Error: Duplicate log importance level: major" << std::endl;
				return false;
			}
		else if (*it == "error")
			if ((accepted_importance & error_lvl) == 0)
				accepted_importance = accepted_importance | error_lvl;
			else
			{
				std::cerr << "Error: Duplicate log importance level: error" << std::endl;
				return false;
			}
		else
		{
			std::cerr << "Error: Unknown log importance level: " << *it << std::endl;
			return false;
		}
	}
	Logger::accept_importance(accepted_importance);
	return true;
}

bool
Arguments::set_help(void)
{
	if (_is_help_set == true)
	{
		std::cerr << "Error: Multiple help options" << std::endl;
		return false;
	}
	_is_help_set = true;
	return true;
}

const std::string &
Arguments::config_path(void) const
{
	return _config_path;
}

const std::string &
Arguments::log_file(void) const
{
	return _log_file;
}

bool
Arguments::apply(int argc, char* argv[])
{
	std::string tmp;

	if (argc > 4)
	{
		std::cerr << "Error: Too many arguments" << std::endl;
		return false;
	}
	for (int i = 1; i < argc; ++i)
	{
		tmp = argv[i];
		if (tmp.find("--") != 0)
		{
			if (set_config_path(tmp) == false)
				return false;
		}
		else if (tmp.find("--log_file=") == 0)
		{
			if (set_log_file(tmp) == false)
				return false;
		}
		else if (tmp.find("--log_importance=") == 0)
		{
			if (set_log_importance(tmp) == false)
				return false;
		}
		else if (tmp.compare("--help") == 0)
		{
			if (set_help() == false)
				return false;
		}
		else
		{
			std::cerr << "Error: Unknown argument: " << tmp << std::endl;
			return false;
		}
	}
	if (_is_help_set == true)
		print_help();
	if (_config_path.empty() == true)
		_config_path = "ressources/config/webserv.conf";
	if (_log_file.empty() == true)
		_log_file = DEFAULT_LOG_FILE;
	return true;
}
