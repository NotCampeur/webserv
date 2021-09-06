#ifndef WEBSERV_RESPONSE_H
# define WEBSERV_RESPONSE_H

# include "webserv.hpp"
# include "StatusCodes.hpp"
# include "RequestConfig.hpp"
# include "HttpErrorManager.hpp"

class Response
{
	public:
		typedef std::pair<std::string, std::string>		header_t;

	private:
		std::string					_payload;
		const std::string			_version;
		StatusCodes::status_index_t _code;
		std::vector<header_t>		_headers;
		bool						_metadata_sent;
		bool						_ready_to_send;
		bool						_complete;
		int							_handler_fd;
		RequestConfig				_config;
		std::string					_file_path;
		HttpErrorManager			_error_manager;
		bool						_path_is_dir;

	public:
	    Response(void);
    	Response(Response const & src);
    	~Response(void);

		Response &  operator=(Response const & src);
		Response &  operator=(const RequestConfig & to_assign);

		// bool				ready_to_send(void) const;
		bool &					complete(void);
		bool					metadata_sent(void) const;
		bool &					ready_to_send(void);
		bool &					path_is_dir(void);
		void					set_http_code(StatusCodes::status_index_t i);
		void					set_payload(const std::string & str);
		//Sends buffer content, first checking if header was sent already, if not, sets it and sends it
		const std::string &		get_payload(void);
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
		
	private:
		void	add_default_headers(void);
		void	set_date(std::string & date);
		void	set_resp_metadata(void);
		void	set_status_line(std::string & meta);
};

#endif
