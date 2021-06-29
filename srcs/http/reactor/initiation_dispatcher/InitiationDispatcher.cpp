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
			_demultiplexer->activate();
			// Think of different implementation as remove handle operations could 
			Demultiplexer::pollfd_arr::iterator	it = _demultiplexer->begin();
			while (it != _demultiplexer->end())
			{
				if (POLLIN == (POLLIN & it->revents))
				{
					Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << it->fd << " ready for reading";

					try {
						int ret = _event_handler_table->get(it->fd)->readable();
						switch (ret)
						{
							case CLIENT_CLOSED_CONNECTION :
							{
								remove_handle(it->fd);
								break ;
							}
							case REQUEST_COMPLETE :
							{
								it->events = POLLOUT;
								it++;
								break ;
							}
							case REQUEST_INCOMPLETE :
							{
								it++;
								break ;
							}
						}
					}
					catch(const std::exception& e)
					{
						Logger(LOG_FILE, error_type) << e.what();
						if (errno == ECONNRESET)
						{
							remove_handle(it->fd);
						}
						else
							break ;
					}
				}
				else if (POLLOUT == (POLLOUT & it->revents))
				{
					Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << it->fd << " ready for writing";

					try {
						_event_handler_table->get(it->fd)->writable();
						// it->events = POLLIN; // Uncomment when timout is implemented
					}
					catch (const std::exception& e)
					{
						// Uncomment to below once Timemout feature is implemented
						if (errno == ECONNRESET || errno == EHOSTDOWN || errno == EHOSTUNREACH)
						// {
						// 	remove_handle(it->fd);
						// }
						// else
						Logger(LOG_FILE, error_type) << e.what();
						break ;
					}
					remove_handle(it->fd);
				}
				else
					it++;
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
