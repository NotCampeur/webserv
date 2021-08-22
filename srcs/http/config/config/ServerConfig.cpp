#include "ServerConfig.hpp"

ServerConfig::ServerConfig(std::string & port, bool autoindex, size_t max_client_body_size) :
_name("NAME_NOT_SET"),
_host("127.0.0.1"),
_port(port),
_error_pages(),
_max_client_body_size(max_client_body_size),
_root_dir("/"),
_index(),
_is_autoindex_on(autoindex),
_default_file_dir(),
_routes()
{}

ServerConfig::ServerConfig(ServerConfig const & src) :
_name(src._name),
_host(src._host),
_port(src._port),
_error_pages(src._error_pages),
_max_client_body_size(src._max_client_body_size),
_root_dir(src._root_dir),
_is_autoindex_on(src._is_autoindex_on),
_default_file_dir(src._default_file_dir),
_routes(src._routes)
{}

ServerConfig::~ServerConfig(void)
{
	size_t size(0);

	size = _routes.size();
	for (size_t i(0); i < size; i++)
		delete _routes[i];
}

// ServerConfig &
// ServerConfig::operator=(ServerConfig const & src)
// {
// 	_error_pages = src._error_pages;
// 	_max_client_body_size = src._max_client_body_size;
// 	_root_dir = src._root_dir;
// 	_autoindex = src._autoindex;
// 	_default_file_dir = src._default_file_dir;
//     return (*this);
// }

const std::string &
ServerConfig::name(void) const
{
	return _name;
}

void
ServerConfig::set_name(std::string & name)
{
	_name = name;
}

const std::string &
ServerConfig::host(void) const
{
	return _host;
}

void
ServerConfig::set_host(std::string & host)
{
	_host = host;
}

const std::string &
ServerConfig::port(void) const
{
	return _port;
}

void
ServerConfig::set_port(std::string & port)
{
	_port = port;
}

const std::string *
ServerConfig::error_page_path(int error) const
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
ServerConfig::max_client_body_size(void) const
{
	return _max_client_body_size;
}

void
ServerConfig::set_max_client_body_size(size_t max_client_body_size)
{
	_max_client_body_size = max_client_body_size;
}

const std::string &
ServerConfig::root_dir(void) const
{
	return _root_dir;
}

void			
ServerConfig::set_root_dir(std::string & root)
{
	_root_dir = root;
}

const std::string &
ServerConfig::index(void) const
{
	return _index;
}

void			
ServerConfig::set_index(std::string & root)
{
	_index = root;
}

bool
ServerConfig::is_autoindex_on(void) const
{
	return _is_autoindex_on;
}

void
ServerConfig::set_autoindex(bool autoindex)
{
	_is_autoindex_on = autoindex;
}

const std::string *
ServerConfig::default_file_dir(void) const
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

const std::vector<RouteConfig *> &
ServerConfig::routes(void) const
{
	return _routes;
}

void
ServerConfig::add_route(RouteConfig * route)
{
	_routes.push_back(route);
}