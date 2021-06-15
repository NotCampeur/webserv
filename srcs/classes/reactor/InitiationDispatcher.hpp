#ifndef INITIATIONDISPATCHER_H
# define INITIATIONDISPATCHER_H

# include "Demultiplexer.hpp"
# include "HandlerTable.hpp"
# include "ClientHandler.hpp"
# include "ServerHandler.hpp"

class InitiationDispatcher
{
		Demultiplexer		* const _demultiplexer;
		HandlerTable		* const _event_handler_table;

	public:
		InitiationDispatcher(void);
		InitiationDispatcher(const InitiationDispatcher & src);
		~InitiationDispatcher(void);

		InitiationDispatcher &	operator=(const InitiationDispatcher & src);

		// Main loop: starts the loop that uses the demultiplexor and call event handlers
		void					handle_events(void);
		void					add_handle(const Server & srv);
		void					add_handle(const Client & clt);
		void					remove_handle(int fd);

		class DemultiplexerNotSet : public std::exception
		{
			const char * what(void) const throw();
		};
		class HandlerTableNotSet : public std::exception
		{
			const char * what(void) const throw();
		};
};

#endif