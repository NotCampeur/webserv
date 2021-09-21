#include "Logger.hpp"

static sem_t *
load_semaphore(void)
{
	sem_t *	result;

	result = sem_open("webserv_logger_lock", O_CREAT, 777, 1);
	sem_unlink("webserv_logger_lock");
	return result;
}

//Static initialisation.
std::ofstream			Logger::_file;
log_importance_level	Logger::_accepted_importance = log_importance_level(error_lvl | major_lvl);
sem_t *					Logger::_multi_process_lock = load_semaphore();
pid_t					Logger::_process_id = getpid();


Logger::Logger(log_type type, log_importance_level importance)
{
	sem_wait(_multi_process_lock); // I don't know if this is the behaviour we want.
									// Because it will make the server block in very rare cases.
									// After all we have done to make it non-blocking.
	_type = type;
	_importance = importance;
	if (is_important_enough())
		put_timestamp();
}

Logger::~Logger()
{
	if (is_important_enough())
		_file << std::endl;
	sem_post(_multi_process_lock);
}

void
Logger::put_timestamp(void)
{
	std::string	msg;
	time_t		now(0);

	now = time(0);
	msg = ctime(&now);
	msg.erase(msg.end() - 1);
	msg = '[' + msg + "] ";
	if (getpid() != _process_id)
		msg += "{'CGI'} ";
	if (_type == error_type)
		msg += "{ERROR} ";
	_file << msg;
}

void
Logger::accept_importance(log_importance_level accepted_importance)
{
	_accepted_importance = accepted_importance;
}

void
Logger::open_log_file(std::string path)
{
	if (_file.is_open() == false)
		_file.open(path.c_str());
}

void
Logger::quit(void)
{
	_file << "End of logs" << std::endl;
	sem_close(_multi_process_lock);
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
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const char * const & entry)
{
	if (is_important_enough() && entry != NULL)
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const char & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const int & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const ssize_t & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}

Logger &
Logger::operator<<(const size_t & entry)
{
	if (is_important_enough())
		_file << entry;
	return *this;
}
