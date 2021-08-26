#ifndef WEBSERV_HttpErrorManager_H
# define WEBSERV_HttpErrorManager_H

# include "webserv.hpp"
# include "StatusCodes.hpp"
class Response;
class ServerConfig;

class HttpErrorManager
{
	public:
		typedef std::map<std::string, const ServerConfig &>	config_type;
	private:
		int						_fd;
		const config_type &	_config;
		Response &				_resp;
	
	public:
		HttpErrorManager(const config_type & config, Response & resp);
		HttpErrorManager(HttpErrorManager const & src);
    	~HttpErrorManager(void);

		void	handle(StatusCodes::status_index_t error);
		void	reset(void);

	private:
		HttpErrorManager(void);
		HttpErrorManager &  operator=(HttpErrorManager const & src);

		void	set_default_msg(StatusCodes::status_index_t error);
		// Fill response payload with default error msg and return payload size
		size_t	set_payload_to_default_msg(StatusCodes::status_index_t error);
		off_t	get_file_size(const std::string & path);
		void	set_content_length_header(off_t len);
		void	set_content_type_header(void);
};

#endif
