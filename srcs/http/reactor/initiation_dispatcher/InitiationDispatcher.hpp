#ifndef WEBSERV_INITIATION_DISPATCHER_HPP
# define WEBSERV_INITIATION_DISPATCHER_HPP

# include "Demultiplexer.hpp"
# include "HandlerTable.hpp"
# include "ClientHandler.hpp"
# include "ServerHandler.hpp"
# include "Exception.hpp"
# include "SYSException.hpp"
# include "ServerSYSException.hpp"
# include "ClientSYSException.hpp"

class InitiationDispatcher
{
	private:
		Demultiplexer		* const _demultiplexer;
		HandlerTable		* const _event_handler_table;

	public:
		InitiationDispatcher(void);
		~InitiationDispatcher(void);

		// Main loop: starts the loop that uses the demultiplexor and call event handlers
		void					handle_events(void);
		void					add_handle(const Server & srv);
		void					add_handle(const Client & clt);
		void					remove_handle(int fd);

	private:
		InitiationDispatcher(const InitiationDispatcher & src);
		InitiationDispatcher &	operator=(const InitiationDispatcher & src);

		void					set_demultiplexer_handles(void);
};

#endif