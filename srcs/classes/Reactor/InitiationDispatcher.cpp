#include "InitiationDispatcher.hpp"

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
	while (1)
	{
		try
		{
			_demultiplexer->activate();

			Demultiplexer::pollfd_arr::iterator	it = _demultiplexer->begin();
			Demultiplexer::pollfd_arr::iterator	ite = _demultiplexer->end();

			// for (; it < ite; it++)
			while (it != ite)
			{
				if (POLLIN == (POLLIN & it->revents))
				{
					_event_handler_table->get(it->fd)->readable();
					it++;
				}
				else if (POLLOUT == (POLLOUT & it->revents))
				{
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
			std::cerr << e.what() << '\n';
		}
	}
}

void
InitiationDispatcher::add_handle(const Server & srv)
{
	ServerHandler *sh = new ServerHandler(srv, *this);
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

	// #ifdef DEBUG
	// std::cout << "FD " << fd << " removed" << '\n';
	// #endif
}