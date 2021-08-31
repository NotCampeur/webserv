#ifndef WEBSERV_LOCATION_CONFIG_HPP
# define WEBSERV_LOCATION_CONFIG_HPP

# include <string>
# include <vector>
# include "ServerConfig.hpp"
# include "Exception.hpp"

class ServerConfig;

typedef enum RouteMethod
{
	NOTHING = 0x000,
	GET = 0x001,
	POST = 0x002,
	DELETE = 0x004,
	HEAD = 0x008,
	ALL = 0xFFF
}	RouteMethod;

class LocationConfig
{
	private:
		std::string							_path;
		RouteMethod							_accepted_method;
		std::string							_redirection;
		std::string							_root;
		bool								_is_autoindex_on;
		std::string							_default_file_dir;
		std::map<std::string, std::string>	_cgi;
		std::string							_upload_path;
								LocationConfig();

	public:
		//Constructors & Destructor
					LocationConfig(ServerConfig & config);
					LocationConfig(std::string path, ServerConfig & config);
					LocationConfig(const LocationConfig & to_copy);
					~LocationConfig();

		//Getters
		std::string							path() const;
		RouteMethod							accepted_method() const;
		std::string							redirection() const;
		std::string							root() const;
		bool								is_autoindex_on() const;
		std::string							default_file_dir() const;
		std::map<std::string, std::string>	cgi() const;
		std::string							upload_path() const;

		//Setters
		void	set_path(std::string path);
		void	set_autoindex(bool value);
		void	set_default_file_dir(std::string value);
		void	add_cgi(std::string key, std::string value);
		void	set_upload_path(std::string value);
		void	set_redirection(std::string value);
		void	set_root(std::string value);
		void	set_accepted_method(RouteMethod value);

		//Operators
		LocationConfig & operator=(const LocationConfig & to_assign);
};

#endif
