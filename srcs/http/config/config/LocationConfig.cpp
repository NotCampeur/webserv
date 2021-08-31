#include "LocationConfig.hpp"

// Constructors & destructor
LocationConfig::LocationConfig() :
	_path(),
	_accepted_method(ALL),
	_redirection(),
	_root(),
	_is_autoindex_on(),
	_default_file_dir(),
	_cgi(),
	_upload_path()
{}

LocationConfig::LocationConfig(ServerConfig & config)
	: _path("NOT_SET"), _accepted_method(ALL), _cgi()
{
	_redirection = "NOT_SET";
	_root = const_cast<std::string &>(config.root_dir());
	_is_autoindex_on = config.is_autoindex_on();
	if (config.default_file_dir() != NULL)
		_default_file_dir = *config.default_file_dir();
	_upload_path = "NOT_SET";
}

LocationConfig::LocationConfig(std::string path, ServerConfig & config)
	: _path(path), _accepted_method(ALL), _cgi()
{
	_redirection = "NOT_SET";
	_root = const_cast<std::string &>(config.root_dir());
	_is_autoindex_on = config.is_autoindex_on();
	std::string * const_tmp = const_cast<std::string *>(config.default_file_dir());
	_default_file_dir = *const_tmp;
	_upload_path = "NOT_SET";
}

LocationConfig::LocationConfig(const LocationConfig & to_copy)
{
	*this = to_copy;
}

LocationConfig::~LocationConfig()
{}

// Getters
std::string
LocationConfig::path() const
{
	return _path;
}

RouteMethod
LocationConfig::accepted_method() const
{
	return _accepted_method;
}

std::string
LocationConfig::redirection() const
{
	return _redirection;
}

std::string
LocationConfig::root() const
{
	return _root;
}

bool
LocationConfig::is_autoindex_on() const
{
	return _is_autoindex_on;
}

std::string
LocationConfig::default_file_dir() const
{
	return _default_file_dir;
}

std::map<std::string, std::string>
LocationConfig::cgi() const
{
	return _cgi;
}

std::string
LocationConfig::upload_path() const
{
	return _upload_path;
}

//Setters
void
LocationConfig::set_path(std::string path)
{
	_path = path;
}

void
LocationConfig::set_autoindex(bool value)
{
	_is_autoindex_on = value;
}

void
LocationConfig::set_default_file_dir(std::string value)
{
	_default_file_dir = value;
}

void
LocationConfig::add_cgi(std::string key, std::string value)
{
	if (_cgi.insert(std::pair<std::string, std::string>(key, value)).second == false)
		throw Exception("You cannot set the same cgi more than once");
}

void
LocationConfig::set_upload_path(std::string value)
{
	_upload_path = value;
}

void
LocationConfig::set_redirection(std::string value)
{
	_redirection = value;
}

void
LocationConfig::set_root(std::string value)
{
	_root = value;
}

void
LocationConfig::set_accepted_method(RouteMethod value)
{
	_accepted_method = value;
}



//Operators
LocationConfig &
LocationConfig::operator=(const LocationConfig & to_copy)
{
	if (this != &to_copy)
	{
		_path = to_copy._path;
		_accepted_method = to_copy._accepted_method;
		_redirection = to_copy._redirection;
		_root = to_copy._root;
		_is_autoindex_on = to_copy._is_autoindex_on;
		_default_file_dir = to_copy._default_file_dir;
		_cgi = to_copy._cgi;
		_upload_path = to_copy._upload_path;
	}
	return *this;
}
