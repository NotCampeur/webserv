#ifndef INITIATIONDISPATCHER_H
# define INITIATIONDISPATCHER_H

# include "Demultiplexer.hpp"
# include "HandlerTable.hpp"

class InitiationDispatcher
{
		Demultiplexer	*_demultiplexer;
		HandlerTable	*_event_handler_table;

	public:
		InitiationDispatcher(void);
		InitiationDispatcher(const InitiationDispatcher & src);
		~InitiationDispatcher(void);

		InitiationDispatcher &	operator=(const InitiationDispatcher & src);
		
		//	Set the demultiplexor to be used by 'handle_events' method
		//	The demultiplexer can only be set once
		void					set_demultiplexer(Demultiplexer &to_set);
		const Demultiplexer &	demultiplexer(void) const;

		//	Set the handler table to be used by 'handle_events' method
		//	The table can only be set once
		void					set_event_handler_table(HandlerTable &to_set);
		const HandlerTable &	event_handler_table(void) const;

		// Main loop: starts the loop that uses the demultiplexor and call event handlers
		void					handle_events(void);

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