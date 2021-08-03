#ifndef SERVERCONFIG_H
# define SERVERCONFIG_H

# include <string>
# include <map>
# include "webserv_param.hpp"

class ServerConfig
{
	private:
		std::string					_name;
		std::string					_host;
		std::string					_port;
		std::map<int, std::string>	_error_pages;
		size_t						_max_client_body_size;
		std::string					_root_dir;
		bool						_autoindex;
		std::string					_default_file_dir;

	public:
		ServerConfig(std::string & port, bool autoindex = false, size_t max_client_body_size = MAX_CLIENT_BODY_SIZE);
    	ServerConfig(ServerConfig const & src);
    	~ServerConfig(void);
		

	// Error pages path: use map
	// Max client body size: use size_t ? Default should be 1M
	// Root directory (default could be workdir/server_content)
	// Autoindex
	// Default file if request is a directory

		const std::string & get_name(void) const;
		void				set_name(std::string & name);

		const std::string & get_host(void) const;
		void				set_host(std::string & host);

		const std::string & get_port(void) const;
		void				set_port(std::string & port);

		const std::string *	get_error_page_path(int error) const;
		void				add_error_page_path(int error, std::string & path);
		
		size_t				get_max_client_body_size(void) const;
		void				set_max_client_body_size(size_t max_client_body_size);

		const std::string &	get_root_dir(void) const;
		void				set_root_dir(std::string & root);
	
		bool				get_autoindex(void) const;
		void				set_autoindex(bool autoindex);
	
		const std::string * get_default_file_dir(void) const;
		void				set_default_file_dir(std::string & path);

	private:
		ServerConfig &  operator=(ServerConfig const & src);

};

#endif
