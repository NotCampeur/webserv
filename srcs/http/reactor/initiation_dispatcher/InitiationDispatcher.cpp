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
		}
		catch (const SYSException & e)
		{
			Logger(LOG_FILE, error_type) << e.what();
			if (errno != EAGAIN)
				break;
			else
				continue;
		}

		Demultiplexer::pollfd_arr::iterator	it = _demultiplexer->begin();
		Demultiplexer::pollfd_arr::iterator	ite = _demultiplexer->end();
		for (;it != ite; it++)
		{
			if (_event_handler_table->find(it->fd) == _event_handler_table->end()) // If fd has been removed from handler table, it should not be inspected
			{
				continue;
			}
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
					if (_event_handler_table->get(it->fd)->is_timeout())	//Only client handlers can timeout for now
					{
						Logger(LOG_FILE, basic_type, debug_lvl) << "Fd " << it->fd << " timed out";
						remove_handle(it->fd);
					}
				}
			}
			catch (const ClientException & e)
			{
				remove_handle(e.getfd());
				Logger(LOG_FILE, basic_type, error_lvl) << e.what() << ' ' << it->fd;
			
			}
			catch (const ClientSYSException & e)
			{
				remove_handle(e.getfd());
				Logger(LOG_FILE, error_type, error_lvl) << e.what() << ' ' << it->fd;
			
			}
			catch (const ServerSYSException & e)
			{
				Logger(LOG_FILE, error_type, error_lvl) << e.what() << ' ' << it->fd;
				return ;
			}
			catch (const Exception & e)
			{
				Logger(LOG_FILE, basic_type, debug_lvl) << e.what() << ' ' << it->fd;
			}
			catch (const SYSException & e)
			{
				remove_handle(it->fd);
				Logger(LOG_FILE, error_type) << e.what();
			}
		}
	}
	Logger(LOG_FILE, basic_type, debug_lvl) << "Leaving main loop handle_events";
}

void
InitiationDispatcher::set_demultiplexer_handles(void)
{
	_demultiplexer->clear();
	HandlerTable::iterator it = _event_handler_table->begin();
	HandlerTable::iterator ite = _event_handler_table->end();
	
	while (it != ite)
	{
		_demultiplexer->addfd(it->first, it->second->get_event_flag());
		it++;
	}
}

void
InitiationDispatcher::add_server_handle(const Server & srv)
{
	ServerHandler *sh = new ServerHandler(&srv);
	_event_handler_table->add(sh->get_serverfd(), *sh);
}

void
InitiationDispatcher::add_client_handle(const Client & clt)
{
	ClientHandler *ch = new ClientHandler(clt);
	_event_handler_table->add(ch->get_clientfd(), *ch);
}

void
InitiationDispatcher::add_read_handle(int fd, size_t file_size, Response & resp)
{
	ReadHandler *rh = new ReadHandler(fd, file_size, resp);
	_event_handler_table->add(fd, *rh);
}

void
InitiationDispatcher::add_write_handle(int fd, const std::string & body, Response & resp)
{
	WriteHandler *wh = new WriteHandler(fd, body, resp);
	_event_handler_table->add(fd, *wh);

}

void
InitiationDispatcher::remove_handle(int fd)
{
	_event_handler_table->remove(fd);
	Logger(LOG_FILE, basic_type, debug_lvl) << "FD " << fd << " removed";
}
