#include "Logger.hpp"

//Static initialisation.
std::string				Logger::_path = std::string();
log_type				Logger::_type = log_type();
Logger::map_type		Logger::_files = Logger::map_type();
log_importance_level	Logger::_accepted_importance = log_importance_level(all_lvl);


Logger::Logger(std::string path, log_type type, log_importance_level importance)
{
	_path = path;
	_type = type;
	_importance = importance;
	if (is_important_enough())
		put_timestamp();
}

Logger::~Logger()
{}

void
Logger::put_timestamp(void)
{
	std::string	msg;
	time_t		now(0);

	if (_files.find(_path) == _files.end())
		_files[_path] = new std::ofstream(_path.c_str());
	now = time(0);
	msg = ctime(&now);
	msg.erase(msg.end() - 1);
	if (_type == error_type)
		msg += " [Error]";
	msg += " : ";
	*_files[_path] << msg;
}

void
Logger::accept_importance(log_importance_level accepted_importance)
{
	_accepted_importance = accepted_importance;
}

void
Logger::quit(void)
{
	map_type::iterator it = _files.begin();
	map_type::iterator ite = _files.end();

	for (; it != ite; it++)
	{
		*it->second << "End of the log";
		delete it->second;
	}
}

bool
Logger::is_important_enough(void) const
{
	if ((_accepted_importance & _importance) != 0)
		return true;
	return false;
}

Logger &
Logger::operator<<(const std::string & entry)
{
	if (is_important_enough())
	{
		*_files[_path] << entry;
	}
	return *this;
}

Logger &
Logger::operator<<(const char * const & entry)
{
	if (is_important_enough())
	{
		*_files[_path] << entry;
	}
	return *this;
}

Logger &
Logger::operator<<(const char & entry)
{
	if (is_important_enough())
	{
		*_files[_path] << entry;
	}
	return *this;
}

Logger &
Logger::operator<<(std::ofstream & entry)
{
	if (is_important_enough())
	{
		(void)entry;
		*_files[_path] << std::endl;
	}
	return *this;
}

Logger &
Logger::operator<<(const int & entry)
{
	if (is_important_enough())
	{
		*_files[_path] << entry;
	}
	return *this;
}


// template <class T>
// Logger &
// operator<<(Logger & logger, T & entry)
// {
// 	if (logger.is_important_enough())
// 	{
// 		std::ostringstream	convert;

// 		convert << entry;
// 		*Logger::_files[Logger::_path] << convert.str();
// 	}
// 	return logger;
// }
