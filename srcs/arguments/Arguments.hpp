#ifndef WEBSERV_ARGUMENTS_HPP
# define WEBSERV_ARGUMENTS_HPP

# include "Singleton.hpp"
#include <iostream>

class Arguments : public Singleton<Arguments>
{
	private:
		std::string	_config_path;
		std::string	_log_file;
		bool		_is_log_importance_set;
		bool		_is_help_set;

		// Will print the program's help and exit.
		void		print_help() const;
		
		bool		set_config_path(const std::string& config_path);
		bool		set_log_file(const std::string& log_file);
		bool		set_log_importance(const std::string importance_level);
		bool		set_help(void);
		
	public:
							Arguments(void);
							~Arguments(void);

		const std::string &	config_path(void) const;
		const std::string &	log_file(void) const;

		bool				apply(int argc, char* argv[]);
};

#endif
