#include "Logger.hpp"

//Static initialisation.
std::string			Logger::_path = std::string();
log_type			Logger::_type = log_type();
Logger::map_type	Logger::_files = Logger::map_type();


Logger::Logger(std::string path, log_type type)
{
	_path = path;
	_type = type;
}

Logger::~Logger()
{}

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

Logger	&
Logger::operator<<(const std::string & entry)
{
	std::string	msg;
	time_t		now(0);

	if (_files.find(_path) == _files.end())
		_files[_path] = new std::ofstream(_path.c_str());
	now = time(0);
	msg = ctime(&now);
	msg.erase(msg.end() - 1);
	if (_type == error)
		msg += " [Error]";
	msg += " : " + entry;
	*_files[_path] << msg << std::endl;
	return *this;
}
