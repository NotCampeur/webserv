#ifndef WEBSERV_LOGGER_HPP
# define WEBSERV_LOGGER_HPP

# include "webserv.hpp"

typedef enum log_type
{
	basic,
	error
}	log_type;

class Logger
{
	public:
		typedef std::map<std::string, std::ofstream *>	map_type;

		Logger(std::string path = LOG_FILE, log_type type = basic);
		~Logger();

		static void	quit(void);

		Logger	&operator<<(const std::string & entry);

	private:
		static std::string	_path;
		static log_type		_type;
		static map_type		_files;
};

#endif
