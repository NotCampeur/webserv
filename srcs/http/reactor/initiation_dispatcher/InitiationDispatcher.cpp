#include "InitiationDispatcher.hpp"

bool g_run_status = true;

InitiationDispatcher::InitiationDispatcher(void) :
_demultiplexer(new Demultiplexer()),
_event_handler_table(new HandlerTable())
{}


InitiationDispatcher::InitiationDispatcher(const InitiationDispatcher & src) :
_demultiplexer(src._demultiplexer),
_event_handler_table(src._event_handler_table)
{}

InitiationDispatcher::~InitiationDispatcher(void)
{
	delete _demultiplexer;
	delete _event_handler_table;
}

void
InitiationDispatcher::handle_events(void)
{
	while (g_run_status)
	{
		try
		{
			_demultiplexer->activate();

			Demultiplexer::pollfd_arr::iterator	it = _demultiplexer->begin();
			Demultiplexer::pollfd_arr::iterator	ite = _demultiplexer->end();

			while (it != ite)
			{
				if (POLLIN == (POLLIN & it->revents))
				{
					Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << it->fd << " ready for reading";
					_event_handler_table->get(it->fd)->readable();
					it->revents = 0;
					it++;
				}
				else if (POLLOUT == (POLLOUT & it->revents))
				{
					Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << it->fd << " ready for writing";
					_event_handler_table->get(it->fd)->writable();
					remove_handle(it->fd);
					ite--;
				}
				else
					it++;
			}

		}
		catch(const std::exception& e)
		{
			Logger(LOG_FILE, error_type) << e.what();
			g_run_status = false;	// FOR TESTING PURPOSES, CONSIDER REMOVING
		}
	}
	Logger(LOG_FILE, basic_type, debug_lvl) << "Leaving main loop handle_events";
}

void
InitiationDispatcher::add_handle(const Server & srv)
{
	ServerHandler *sh = new ServerHandler(&srv, *this);
	_event_handler_table->add(sh->get_serverfd(), *sh);
	_demultiplexer->addfd(sh->get_serverfd());
}

void
InitiationDispatcher::add_handle(const Client & clt)
{
	ClientHandler *ch = new ClientHandler(clt);
	_event_handler_table->add(ch->get_clientfd(), *ch);
	_demultiplexer->addfd(ch->get_clientfd());
}

void
InitiationDispatcher::remove_handle(int fd)
{
	_event_handler_table->remove(fd);
	_demultiplexer->removefd(fd);

	Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << fd << " removed";
}
