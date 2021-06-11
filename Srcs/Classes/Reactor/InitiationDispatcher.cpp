#include "InitiationDispatcher.hpp"

InitiationDispatcher::InitiationDispatcher(void)
: _demultiplexer(NULL), _event_handler_table(NULL)
{}

InitiationDispatcher::InitiationDispatcher(const InitiationDispatcher & src)
{
	*this = src;
}

InitiationDispatcher::~InitiationDispatcher(void)
{}

//It is not a deep copy.
InitiationDispatcher &  
InitiationDispatcher::operator=(const InitiationDispatcher & src)
{
	if (this != &src)
	{
		_demultiplexer = src._demultiplexer;
		_event_handler_table = src._event_handler_table;
	}
	return *this;
};

void 
InitiationDispatcher::set_demultiplexer(Demultiplexer &to_set)
{
	if (_demultiplexer == NULL)
	_demultiplexer = &to_set;
};

const Demultiplexer &
InitiationDispatcher::demultiplexer(void) const
{
	if (_demultiplexer == NULL)
		throw DemultiplexerNotSet();
	return *_demultiplexer;
}

void 
InitiationDispatcher::set_event_handler_table(HandlerTable &to_set)
{
	if (_event_handler_table == NULL)
	_event_handler_table = &to_set;
};

const HandlerTable &
InitiationDispatcher::event_handler_table(void) const
{
	if (_event_handler_table == NULL)
		throw HandlerTableNotSet();
	return *_event_handler_table;
}

void
InitiationDispatcher::handle_events(void)
{
	while (1)
	{
		if (_demultiplexer == NULL)
			throw DemultiplexerNotSet();
		if (_event_handler_table == NULL)
			throw HandlerTableNotSet();
		try
		{
			Demultiplexer::fd_type	fds;
			size_t					size;

			_demultiplexer->activate();
			fds = _demultiplexer->fds();
			size = fds.size();
			for (size_t i(0); i < size; i++)
				if (POLLIN == (POLLIN & fds[i].revents))
					_event_handler_table->get(fds[i].fd)->readable();
				else if (POLLOUT == (POLLOUT & fds[i].revents))
					_event_handler_table->get(fds[i].fd)->writable();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}

const char *
InitiationDispatcher::DemultiplexerNotSet::what(void) const throw()
{
	return ("The demultiplexer is not set in the initiation dispatcher.");
}

const char *
InitiationDispatcher::HandlerTableNotSet::what(void) const throw()
{
	return ("The handler table is not set in the initiation dispatcher.");
}
