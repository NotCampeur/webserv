#ifndef WEBSERV_SERVER_HANDLER_HPP
# define WEBSERV_SERVER_HANDLER_HPP

# include "IEventHandler.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "SystemException.hpp"
# include "ServerSystemException.hpp"
# include "ClientSystemException.hpp"

class InitiationDispatcher;
# include "InitiationDispatcher.hpp"

class ServerHandler : public IEventHandler
{
	private:
		const Server &			_server;
		int						_event_flag;

	public:
		ServerHandler(const Server * server);
		ServerHandler(ServerHandler const & src);
		~ServerHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

		int			 	get_serverfd(void) const;

	private:
		ServerHandler(void);
		void	new_client_handler(Client & client);
		ServerHandler &  operator=(ServerHandler const & src);
};

#endif
