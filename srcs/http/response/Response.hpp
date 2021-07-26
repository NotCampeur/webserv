#ifndef WEBSERV_RESPONSE_H
# define WEBSERV_RESPONSE_H

# include "webserv.hpp"
# include "StatusCodes.hpp"
# include "ServerConfig.hpp"

class Response
{
	public:
		typedef std::pair<std::string, std::string>	header_t;

	private:
		std::string						_payload;
		const std::string				_version;
		StatusCodes::status_index_t 	_code;
		std::vector<header_t>			_headers;
		bool							_metadata_sent;
		bool							_ready_to_send;
		bool							_complete;
		int								_handler_fd;
		const ServerConfig &			_server_config;
		std::string						_file_path;

	public:

    	Response(const ServerConfig & config);
    	Response(Response const & src);
    	~Response(void);

		Response &  operator=(Response const & src);

		// bool				ready_to_send(void) const;
		bool &					complete(void);
		bool					metadata_sent(void) const;
		bool &					ready_to_send(void);
		void					set_http_code(StatusCodes::status_index_t i);
		void					set_payload(const std::string & str);
		void					add_header(const std::string & name, const std::string & value);
		//Sends buffer content, first checking if header was sent already, if not, sets it and sends it
		const std::string &		get_payload(void);
		void					reset(void);
		void					set_http_error(StatusCodes::status_index_t error);
		void					set_error_default_msg(StatusCodes::status_index_t error);
		void					set_handler_fd(int fd);
		int						get_handler_fd(void) const;
		void					payload_erase(size_t len);
		const std::string & 	get_path(void) const;
		void					set_path(const std::string & path);
		const ServerConfig &	get_server_config(void) const;

	private:
	    Response(void);

		void				add_default_headers(void);
		void				set_date(std::string & date);
		void				set_resp_metadata(void);
		void				set_status_line(std::string & meta);
		void				add_error_msg(void);
		void				set_payload_to_default_error_msg(StatusCodes::status_index_t error);
		off_t				get_file_size(const std::string & path);
};

#endif
