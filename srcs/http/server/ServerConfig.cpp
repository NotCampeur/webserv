#include "ServerConfig.hpp"

ServerConfig::ServerConfig(bool autoindex, size_t max_client_body_size) :
_max_client_body_size(max_client_body_size),
_autoindex(autoindex)
{}

ServerConfig::ServerConfig(ServerConfig const & src) :
_error_pages(src._error_pages),
_max_client_body_size(src._max_client_body_size),
_root_dir(src._root_dir),
_autoindex(src._autoindex),
_default_file_dir(src._default_file_dir)
{}

ServerConfig::~ServerConfig(void) {}

ServerConfig &
ServerConfig::operator=(ServerConfig const & src)
{
	_error_pages = src._error_pages;
	_max_client_body_size = src._max_client_body_size;
	_root_dir = src._root_dir;
	_autoindex = src._autoindex;
	_default_file_dir = src._default_file_dir;
    return (*this);
}

const std::string *
ServerConfig::get_error_page_path(int error) const
{

	if (_error_pages.find(error) == _error_pages.end())
		return NULL;
	else
		return &(_error_pages.find(error)->second);
}

void			
ServerConfig::add_error_page_path(int error, std::string & path)
{
	_error_pages.insert(std::pair<int, std::string>(error, path));
}

size_t			
ServerConfig::get_max_client_body_size(void) const
{
	return _max_client_body_size;
}

const std::string &
ServerConfig::get_root_dir(void) const
{
	return _root_dir;
}

void			
ServerConfig::set_root_dir(std::string & root)
{
	_root_dir = root;
}

bool
ServerConfig::get_autoindex(void) const
{
	return _autoindex;
}

void
ServerConfig::set_autoindex(bool autoindex)
{
	_autoindex = autoindex;
}

const std::string *
ServerConfig::get_default_file_dir(void) const
{
	if (_default_file_dir.empty())
		return NULL;
	return &_default_file_dir;
}

void			
ServerConfig::set_default_file_dir(std::string & path)
{
	_default_file_dir = path;
}

