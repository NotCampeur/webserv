#include "ServerConfig.hpp"

ServerConfig::ServerConfig(void) :
_name("NAME_NOT_SET"),
_ip("127.0.0.1"),
_port("8080"),
_error_pages(),
_max_client_body_size(MAX_CLIENT_BODY_SIZE),
_locations()
{}

ServerConfig::ServerConfig(ServerConfig const & src) :
_name(src._name),
_ip(src._ip),
_port(src._port),
_error_pages(src._error_pages),
_max_client_body_size(src._max_client_body_size),
_locations(src._locations)
{}

ServerConfig::~ServerConfig(void)
{
	size_t size(0);

	size = _locations.size();
	for (size_t i(0); i < size; i++)
		delete _locations[i];
}

ServerConfig &
ServerConfig::operator=(ServerConfig const & src)
{
	if (this != &src)
	{
		_name = src._name;
		_ip = src._ip;
		_port = src._port;
		_error_pages = src._error_pages;
		_max_client_body_size = src._max_client_body_size;
		for (size_t i(0); i < src._locations.size(); i++)
			_locations.push_back(new LocationConfig(*src._locations[i]));
	}
    return (*this);
}

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
ServerConfig::ip(void) const
{
	return _ip;
}

void
ServerConfig::set_ip(std::string & ip)
{
	_ip = ip;
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

const std::map<int, std::string> &
ServerConfig::error_page_path(void) const
{
	return _error_pages;
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

const std::vector<LocationConfig *> &
ServerConfig::locations(void) const
{
	return _locations;
}

void
ServerConfig::add_location(LocationConfig * location)
{
	_locations.push_back(location);
}

const std::string *
ServerConfig::cgi_path(const std::string & cgi_ext) const
{
	const std::vector<LocationConfig *> & rt = locations();
	for (size_t i = 0; i < rt.size(); i++)
	{
		if ((rt[i]->cgi().find(cgi_ext)) != rt[i]->cgi().end())
		{
			return &(rt[i]->cgi().find(cgi_ext)->second);
		}
	}
	return NULL;
}
