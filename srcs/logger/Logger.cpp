#include "Logger.hpp"

//Static initialisation.
std::string				Logger::_path = std::string();
log_type				Logger::_type = log_type();
Logger::map_type		Logger::_files = Logger::map_type();
log_importance_level	Logger::_accepted_importance = log_importance_level(all_lvl);
sem_t *					Logger::_multi_process_lock = sem_open("webserv_logger_lock", O_CREAT, 777, 0);


Logger::Logger(std::string path, log_type type, log_importance_level importance)
{
	_path = path;
	_type = type;
	_importance = importance;
	if (is_important_enough())
		put_timestamp();
}

Logger::~Logger()
{
	if (is_important_enough())
		*_files[_path] << std::endl;
}

void
Logger::put_timestamp(void)
{
	std::string	msg;
	time_t		now(0);

	if (_files.find(_path) == _files.end())
	{
		_files.insert(std::pair<std::string, std::ofstream *>(_path, new std::ofstream(_path.c_str())));
	}
	now = time(0);
	msg = ctime(&now);
	msg.erase(msg.end() - 1);
	*_files[_path] << '[' << msg << "] ";
	if (_type == error_type)
		*_files[_path] << "{ERROR} ";
}

void
Logger::accept_importance(log_importance_level accepted_importance)
{
	_accepted_importance = accepted_importance;
}

void
Logger::process_forked(void)
{
	sem_post(_multi_process_lock);
}


void
Logger::quit(void)
{
	if (sem_trywait(_multi_process_lock) == -1)
	{
		map_type::iterator it = _files.begin();

		for (; it != _files.end(); it++)
		{
			*it->second << "End of logs" << std::endl;
			delete it->second;
		}
		_files.clear();
		sem_close(_multi_process_lock);
	}
}

bool
Logger::is_important_enough(void) const
{
	if ((_accepted_importance & _importance) != 0)
		return true;
	return false;
}

log_importance_level
operator|(const log_importance_level & value_a, const log_importance_level & value_b)
{
	return ((log_importance_level)(static_cast<int>(value_a) | static_cast<int>(value_b)));
}

log_importance_level
operator^(const log_importance_level & value_a, const log_importance_level & value_b)
{
	return ((log_importance_level)(static_cast<int>(value_a) ^ static_cast<int>(value_b)));
}

Logger &
Logger::operator<<(const std::string & entry)
{
	if (is_important_enough())
		*_files[_path] << entry;
	return *this;
}

Logger &
Logger::operator<<(const char * const & entry)
{
	if (is_important_enough() && entry != NULL)
		*_files[_path] << entry;
	return *this;
}

Logger &
Logger::operator<<(const char & entry)
{
	if (is_important_enough())
		*_files[_path] << entry;
	return *this;
}

Logger &
Logger::operator<<(const int & entry)
{
	if (is_important_enough())
		*_files[_path] << entry;
	return *this;
}

Logger &
Logger::operator<<(const ssize_t & entry)
{
	if (is_important_enough())
		*_files[_path] << entry;
	return *this;
}

Logger &
Logger::operator<<(const size_t & entry)
{
	if (is_important_enough())
		*_files[_path] << entry;
	return *this;
}
