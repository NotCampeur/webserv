#ifndef WEBSERV_CLIENT_HANDLER_HPP
# define WEBSERV_CLIENT_HANDLER_HPP

# include "IEventHandler.hpp"
# include "Client.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "RequestParser.hpp"
# include "Timeout.hpp"
# include "Exception.hpp"
# include "ClientException.hpp"
# include "ClientSYSException.hpp"

class ClientHandler : public IEventHandler
{
	private:

		const Client &			_client;
		Request					_request;
		Response				_response;
		RequestParser			_req_parser;
		Timeout					_timeout;
		int						_event_flag;

	public:

		ClientHandler(const Client & client);
		~ClientHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

		int				get_clientfd(void) const;

	private:
		ClientHandler(ClientHandler const & src);
		void	set_header(std::stringstream & header, size_t content_length);
};

#endif
