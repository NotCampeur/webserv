#ifndef WEBSERV_LOCATION_CONFIG_HPP
# define WEBSERV_LOCATION_CONFIG_HPP

# include <string>
# include <vector>
# include "ServerConfig.hpp"
# include "Exception.hpp"

class ServerConfig;

typedef enum HTTPMethod
{
	NOTHING = 0x000,
	GET = 0x001,
	POST = 0x002,
	DELETE = 0x004,
	HEAD = 0x008,
	ALL = 0xFFF
}	HTTPMethod;

class LocationConfig
{
	private:
		std::string							_path;
		HTTPMethod							_accepted_method;
		std::pair<int, std::string>			_redirection;
		std::string							_root;
		bool								_is_autoindex_on;
		std::string							_default_file_dir;
		std::map<std::string, std::string>	_cgi;
		std::string							_upload_path;

	public:
		//Constructors & Destructor
					LocationConfig();
					LocationConfig(std::string path);
					LocationConfig(const LocationConfig & to_copy);
					~LocationConfig();

		//Getters
		const std::string							& path() const;
		const HTTPMethod							& accepted_method() const;
		const std::pair<int, std::string>			& redirection() const;
		const std::string							& root() const;
		bool										is_autoindex_on() const;
		const std::string							& default_file_dir() const;
		const std::map<std::string, std::string> 	& cgi() const;
		const std::string							& upload_path() const;

		//Setters
		void	set_path(std::string path);
		void	set_autoindex(bool value);
		void	set_default_file_dir(std::string value);
		void	add_cgi(std::string key, std::string value);
		void	set_upload_path(std::string value);
		void	set_redirection(int type, std::string path);
		void	set_root(std::string value);
		void	set_accepted_method(HTTPMethod value);

		//Operators
		LocationConfig & operator=(const LocationConfig & to_assign);
};

#endif
