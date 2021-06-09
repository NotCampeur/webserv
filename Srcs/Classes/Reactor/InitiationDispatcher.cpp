#include "InitiationDispatcher.hpp"

InitiationDispatcher::InitiationDispatcher(void)
{}
InitiationDispatcher::InitiationDispatcher(const InitiationDispatcher & src)
{}
InitiationDispatcher::~InitiationDispatcher(void)
{}

InitiationDispatcher &  
InitiationDispatcher::operator=(const InitiationDispatcher & src)
{};


void 
InitiationDispatcher::set_demultiplexer(Demultiplexer &d)
{};

Demultiplexer &
InitiationDispatcher::get_demultiplexer(void) const;
        
void
InitiationDispatcher::handle_events(void);