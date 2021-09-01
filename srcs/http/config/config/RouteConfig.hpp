#ifndef WEBSERV_ROUTE_CONFIG_HPP
# define WEBSERV_ROUTE_CONFIG_HPP

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

class RouteConfig
{
	private:
		std::string							_path;
		RouteMethod							_accepted_method;
		std::string							_redirection;
		std::string							_root; //
		bool								_is_autoindex_on;
		std::string							_default_file_dir;
		std::map<std::string, std::string>	_cgi;
		std::string							_upload_path;
								RouteConfig();

	public:
		//Constructors & Destructor
					RouteConfig(ServerConfig & config);
					RouteConfig(std::string path, ServerConfig & config);
					RouteConfig(const RouteConfig & to_copy);
					~RouteConfig();

		//Getters
		std::string							path() const;
		RouteMethod							accepted_method() const;
		std::string							redirection() const;
		std::string							root() const;
		bool								is_autoindex_on() const;
		std::string							default_file_dir() const;
		const std::map<std::string, std::string> & get_cgi() const;
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
		RouteConfig & operator=(const RouteConfig & to_assign);
};

#endif
