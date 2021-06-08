#ifndef INITIATIONDISPATCHER_H
# define INITIATIONDISPATCHER_H

# include "demultiplexer.hpp"
# include "handlerTable.hpp"

class initiationDispatcher
{

    public:
        initiationDispatcher(void);
        initiationDispatcher(initiationDispatcher const & src);
        ~initiationDispatcher(void);

        initiationDispatcher &  operator=(initiationDispatcher const & src);
        //set the demultiplexor to be used by 'handle_events' method
        void set_demultiplexor(demultiplexer &d);
        demultiplexer & get_demultiplexer(void) const;

        // Add/remove envent handlers to event_handler_table
        void add_event_handler(IeventHandler &eh);
        void remove_event_handler(handlerTable::handle_type handle);

        // Main loop: starts the loop that uses the demultiplexor and call event handlers
        void handle_events(void);

    private:
        demultiplexer & _demultiplexer;
        handlerTable & _event_handler_table;

};

#endif