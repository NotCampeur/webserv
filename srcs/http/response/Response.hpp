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
		bool							_header_sent;
		bool							_ready_to_send;
		bool							_complete;

	public:

    	Response(void);
    	Response(Response const & src);
    	~Response(void);

		Response &  operator=(Response const & src);

		bool				ready_to_send(void) const;
		bool				iscomplete(void) const;
		bool				header_sent(void) const;
		void				make_ready(void);
		void				make_complete(void);
		void				set_http_code(StatusCodes::status_index_t i);
		void				fill_payload(const std::string & str);
		void				add_header(const std::string & name, const std::string & value);
		const std::string &	get_location(void);
		//Sends buffer content, first checking if header was sent already, if not, sets it and sends it
		const std::string &	send(void);
		void				reset(void);

	private:
		void				set_default_headers(void);
		void				set_date(void);
		void				set_resp_header(void);
};

#endif
