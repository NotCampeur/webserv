#ifndef WEBSERV_RESPONSE_H
# define WEBSERV_RESPONSE_H

# include "webserv.hpp"
# include "StatusCodes.hpp"
# include "RequestConfig.hpp"
# include "HttpErrorManager.hpp"
class ServerConfig;
class Request;

class Response
{
	public:
		typedef std::pair<std::string, std::string>		header_t;

		// typedef const ServerConfig & (Request::*get_config_t)(void);

	private:
		std::vector<char>				_payload;
		const std::string				_version;
		StatusCodes::status_index_t 	_code;
		std::vector<header_t>			_headers;	//Using a vector to order headers properly (e.g. good practice to send date first)
		bool							_metadata_sent;
		bool							_ready_to_send;
		bool							_complete;
		int								_handler_fd;
		// RequestConfig					_config;
		const Request &					_req;
		std::string						_file_path;
		HttpErrorManager				_error_manager;
		bool							_path_is_dir;
		bool							_need_cgi;
		bool							_chunked;
		const std::string				_server_ip;
		const std::string				_client_ip;			
		const std::string				_client_port;	

	public:
    	// Response(const ServerConfig & (Request::*get_config)(void));
		Response(const Request & req, const std::string & server_ip, const std::string & client_ip, const std::string & _client_port);
		// Response(const config_type & config);
		// Response(void);
    	Response(Response const & src);
    	~Response(void);

		Response &  operator=(Response const & src);
		// Response &  operator=(const RequestConfig & to_assign);

		const std::string &		get_ip(void);
		bool &					complete(void);
		bool					metadata_sent(void) const;
		bool &					ready_to_send(void);
		bool &					path_is_dir(void);
		bool &					need_cgi(void);
		void					set_http_code(StatusCodes::status_index_t i);
		void					set_payload(const char *buf, size_t len);
		//Sends buffer content, first checking if header was sent already, if not, sets it and sends it
		//Returns a pair with the first argument set to the return value of function send(), and the second set to the initial size of the buffer
		int						send_payload(int fd);
		void					payload_erase(size_t len);
		
		void					add_header(const std::string & name, const std::string & value);
		
		void					set_handler_fd(int fd);
		int						get_handler_fd(void) const;

		void					set_path(const std::string & path);
		const std::string & 	get_path(void) const;

		const RequestConfig &	config(void) const;
		void					reset(void);
		void					http_error(StatusCodes::status_index_t error);
		void					http_redirection(StatusCodes::status_index_t code, const std::string & location);
		void					send_chunks(void);
		const std::string &		get_server_ip(void) const;
		const std::string &		get_client_ip(void) const;
		const std::string &		get_client_port(void) const;

	private:
		void	add_default_headers(void);
		void	set_date(std::string & date);
		void	set_resp_metadata(void);
		std::string	get_status_line(void);
		void	add_payload_crlf(void);
		void	insert_chunk_size(size_t len);
		void	add_last_chunk(void);
};

#endif
