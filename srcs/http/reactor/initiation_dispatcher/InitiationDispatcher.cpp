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
		try {
			set_demultiplexer_handles();
			_demultiplexer->activate();
			Demultiplexer::pollfd_arr::iterator	it = _demultiplexer->begin();
			Demultiplexer::pollfd_arr::iterator	ite = _demultiplexer->end();
			for (;it != ite; it++)
			{
				try {
					if (POLLIN == (POLLIN & it->revents))
					{
						Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << it->fd << " ready for reading";
						_event_handler_table->get(it->fd)->readable();
					}
					else if (POLLOUT == (POLLOUT & it->revents))
					{
						Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << it->fd << " ready for writing";
						_event_handler_table->get(it->fd)->writable();
						it->events = POLLIN;
					}
					else if (_event_handler_table->get(it->fd)->is_timeoutable())
					{
						std::cerr << "Timeout check: ";
						if (_event_handler_table->get(it->fd)->is_timeout())
						{
							Logger(LOG_FILE, basic_type, debug_lvl) << "Fd " << it->fd << " timed out";
							remove_handle(it->fd);
							std::cerr << "REMOVED\n";
						}
						else
						{
							std::cerr << "Not timeout yet\n";
						}
					}
				}
				catch (const ClientHandler::ClientClosedConnection & e)
				{
					remove_handle(it->fd);
					Logger(LOG_FILE, basic_type, debug_lvl) << e.what() << ' ' << it->fd;
				}
				catch (const std::exception& e)
				{
					remove_handle(it->fd);
					Logger(LOG_FILE, error_type) << e.what();
				}
			}
		}
		catch (const std::exception & e)
		{
			Logger(LOG_FILE, error_type) << e.what();
			if (errno != EAGAIN)
				break ;
		}
	}
	Logger(LOG_FILE, basic_type, debug_lvl) << "Leaving main loop handle_events";
}

void
InitiationDispatcher::set_demultiplexer_handles(void)
{
	HandlerTable::iterator it = _event_handler_table->begin();
	HandlerTable::iterator ite = _event_handler_table->end();

	_demultiplexer->clear();
	while (it != ite)
	{
		_demultiplexer->addfd(it->first, it->second->get_event_flag());
		it++;
	}
}

void
InitiationDispatcher::add_handle(const Server & srv)
{
	ServerHandler *sh = new ServerHandler(&srv, *this);
	_event_handler_table->add(sh->get_serverfd(), *sh);
}

void
InitiationDispatcher::add_handle(const Client & clt)
{
	ClientHandler *ch = new ClientHandler(clt);
	_event_handler_table->add(ch->get_clientfd(), *ch);
}

void
InitiationDispatcher::remove_handle(int fd)
{
	_event_handler_table->remove(fd);

	Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << fd << " removed";
}
