#ifndef WEBSERV_CLIENT_HANDLER_HPP
# define WEBSERV_CLIENT_HANDLER_HPP

# include "IEventHandler.hpp"
# include "Client.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "RequestParser.hpp"
# include "Timer.hpp"
# include "Exception.hpp"
# include "ClientException.hpp"
# include "ClientSYSException.hpp"
# include "StatusCodes.hpp"

class ClientHandler : public IEventHandler
{
	private:

		const Client &					_client;
		Request							_request;
		Response						_response;
		RequestParser					_req_parser;
		const Timer						_timer;
		int								_event_flag;

	public:

		ClientHandler(const Client & client);
		ClientHandler(ClientHandler const & src);
		~ClientHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;
		int				get_clientfd(void) const;

	private:
		ClientHandler &	operator=(ClientHandler const & src);
		void			handle_request(void);
		void			parse_request(void);
		void			handle_http_error(StatusCodes::status_index_t error_code);
		// void	set_header(std::stringstream & header, size_t content_length);
};

#endif
