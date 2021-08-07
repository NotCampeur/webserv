#include "RouteConfig.hpp"

// Constructors & destructor
RouteConfig::RouteConfig() :
	_path(),
	_accepted_method(ALL),
	_redirection(),
	_root(),
	_is_autoindex_on(),
	_default_file_dir(),
	_cgi(),
	_upload_path()
{}

RouteConfig::RouteConfig(ServerConfig & config)
	: _path("NOT_SET"), _accepted_method(ALL)
{
	_redirection = "NOT_SET";
	_root = const_cast<std::string &>(config.root_dir());
	_is_autoindex_on = config.is_autoindex_on();
	std::string * const_tmp = const_cast<std::string *>(config.default_file_dir());
	_default_file_dir = *const_tmp;
	_cgi = "NOT_SET";
	_upload_path = "NOT_SET";
}

RouteConfig::RouteConfig(std::string path, ServerConfig & config)
	: _path(path), _accepted_method(ALL)
{
	_redirection = "NOT_SET";
	_root = const_cast<std::string &>(config.root_dir());
	_is_autoindex_on = config.is_autoindex_on();
	std::string * const_tmp = const_cast<std::string *>(config.default_file_dir());
	_default_file_dir = *const_tmp;
	_cgi = "NOT_SET";
	_upload_path = "NOT_SET";
}

RouteConfig::RouteConfig(const RouteConfig & to_copy)
	: _path(to_copy._path), _accepted_method(to_copy._accepted_method)
{
	*this = to_copy;
}

RouteConfig::~RouteConfig()
{}

// Getters
std::string
RouteConfig::path() const
{
	return _path;
}

RouteMethod
RouteConfig::accepted_method() const
{
	return _accepted_method;
}

std::string
RouteConfig::redirection() const
{
	return _redirection;
}

std::string
RouteConfig::root() const
{
	return _root;
}

bool
RouteConfig::is_autoindex_on() const
{
	return _is_autoindex_on;
}

std::string
RouteConfig::default_file_dir() const
{
	return _default_file_dir;
}

std::string
RouteConfig::cgi() const
{
	return _cgi;
}

std::string
RouteConfig::upload_path() const
{
	return _upload_path;
}

//Setters
void
RouteConfig::set_path(std::string path)
{
	_path = path;
}

void
RouteConfig::set_autoindex(bool value)
{
	_is_autoindex_on = value;
}

void
RouteConfig::set_default_file_dir(std::string value)
{
	_default_file_dir = value;
}

void
RouteConfig::set_cgi(std::string value)
{
	_cgi = value;
}

void
RouteConfig::set_upload_path(std::string value)
{
	_upload_path = value;
}

void
RouteConfig::set_redirection(std::string value)
{
	_redirection = value;
}

void
RouteConfig::set_root(std::string value)
{
	_root = value;
}

void
RouteConfig::set_accepted_method(RouteMethod value)
{
	_accepted_method = value;
}



//Operators
RouteConfig &
RouteConfig::operator=(const RouteConfig & to_copy)
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
