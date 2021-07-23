#ifndef WEBSERV_RESPONSE_H
# define WEBSERV_RESPONSE_H

# include "webserv.hpp"
# include "StatusCodes.hpp"

# define DEFAULT_HEADERS_COUNT 3
# define SERVER_HEADER_INDEX 0
# define DATE_HEADER_INDEX 1
# define LOCATION_HEADER_INDEX 2

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

	public:

    	Response(void); // Initialize with ref to error pages locations
    	Response(Response const & src);
    	~Response(void);

		Response &  operator=(Response const & src);

		// bool				ready_to_send(void) const;
		bool &				complete(void);
		bool				metadata_sent(void) const;
		bool &				ready_to_send(void);
		void				set_http_code(StatusCodes::status_index_t i);
		void				set_payload(const std::string & str);
		void				add_header(const std::string & name, const std::string & value);
		const std::string &	get_location(void);
		//Sends buffer content, first checking if header was sent already, if not, sets it and sends it
		const std::string &	get_payload(void);
		void				reset(void);
		void				http_error(StatusCodes::status_index_t error);
		void				set_handler_fd(int fd);
		int					get_handler_fd(void) const;
		void				payload_erase(size_t len);

	private:
		void				add_default_headers(void);
		void				set_date(std::string & date);
		void				set_resp_metadata(void);
		void				set_status_line(std::string & meta);
		void				add_error_msg(void);
};

#endif
