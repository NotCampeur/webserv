#ifndef SERVERCONFIG_H
# define SERVERCONFIG_H

# include <string>
# include <map>
# include "webserv_param.hpp"

class ServerConfig
{
	private:
		const std::string			_name;
		const std::string			_port;
		std::map<int, std::string>	_error_pages;
		size_t						_max_client_body_size;
		std::string					_root_dir;
		bool						_autoindex;
		std::string					_default_file_dir;
		std::map<const std::string, const std::string> _cgi_paths;

	public:
		ServerConfig(std::string & name, std::string & port, bool autoindex = false, size_t max_client_body_size = MAX_CLIENT_BODY_SIZE);
    	ServerConfig(ServerConfig const & src);
    	~ServerConfig(void);

	// Error pages path: use map
	// Max client body size: use size_t ? Default should be 1M
	// Root directory (default could be workdir/server_content)
	// Autoindex
	// Default file if request is a directory

		const std::string & get_name(void) const;
		const std::string & get_port(void) const;

		const std::string *	get_error_page_path(int error) const;
		void				add_error_page_path(int error, std::string & path);
		
		size_t				get_max_client_body_size(void) const;

		const std::string &	get_root_dir(void) const;
		void				set_root_dir(std::string & root);
	
		bool				get_autoindex(void) const;
		void				set_autoindex(bool autoindex);
	
		const std::string * get_default_file_dir(void) const;
		void				set_default_file_dir(std::string & path);

		const std::string *	get_cgi_path(const std::string cgi_ext) const;
		void				add_cgi_path(const std::string & cgi_ext, const std::string & path);


	private:
		ServerConfig &  operator=(ServerConfig const & src);

};

#endif
