#ifndef INITIATIONDISPATCHER_H
# define INITIATIONDISPATCHER_H

# include "demultiplexer.hpp"
# include "HandlerTable.hpp"

class InitiationDispatcher
{

    public:
        InitiationDispatcher(void);
        InitiationDispatcher(const InitiationDispatcher & src);
        ~InitiationDispatcher(void);

        InitiationDispatcher &  operator=(const InitiationDispatcher & src);
        
        //set the demultiplexor to be used by 'handle_events' method
        void set_demultiplexer(Demultiplexer &d);
        Demultiplexer & get_demultiplexer(void) const;

        // Main loop: starts the loop that uses the demultiplexor and call event handlers
        void handle_events(void);

    private:
        Demultiplexer _demultiplexer;
        HandlerTable _event_handler_table;

};

#endif