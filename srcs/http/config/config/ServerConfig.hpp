#ifndef SERVERCONFIG_H
# define SERVERCONFIG_H

# include <string>
# include <vector>
# include <map>
# include "webserv_param.hpp"
# include "LocationConfig.hpp"

class LocationConfig;

class ServerConfig
{
	private:
		std::string						_name;
		std::string						_ip;
		std::string						_port;
		std::map<int, std::string>		_error_pages;
		size_t							_max_client_body_size;
		std::vector<LocationConfig *>	_locations;

	public:
		ServerConfig(void);
    	ServerConfig(ServerConfig const & src);
    	~ServerConfig(void);

		const std::string & name(void) const;
		void				set_name(std::string & name);

		const std::string & ip(void) const;
		void				set_ip(std::string & ip);

		const std::string & port(void) const;
		void				set_port(std::string & port);

		const std::map<int, std::string> &	get_all_error_pages(void) const;
		const std::string *					error_page_path(int error) const;
		void								add_error_page_path(int error, std::string & path);

		size_t				max_client_body_size(void) const;
		void				set_max_client_body_size(size_t max_client_body_size);

		const std::vector<LocationConfig *> & locations(void) const;
		void				add_location(LocationConfig * location);

		const std::string * cgi_path(const std::string & cgi_ext) const;

	private:
		ServerConfig &  operator=(ServerConfig const & src);
};

#endif
