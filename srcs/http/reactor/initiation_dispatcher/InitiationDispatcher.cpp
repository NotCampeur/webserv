# include "InitiationDispatcher.hpp"
# include "ClientHandler.hpp"
# include "ServerHandler.hpp"
# include "ReadHandler.hpp"
# include "WriteHandler.hpp"
# include "CgiHandler.hpp"
# include "Exception.hpp"
# include "SystemException.hpp"
# include "ServerSystemException.hpp"
# include "ClientSystemException.hpp"

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
		catch (const SystemException & e)
		{
			Logger(error_type, error_lvl) << e.what();
			// if (errno != EAGAIN)
				break;
			// else
				// continue;
		}
		Demultiplexer::pollfd_arr::iterator	it = _demultiplexer->begin();
		Demultiplexer::pollfd_arr::iterator	ite = _demultiplexer->end();
		for (;it != ite; it++)
		{
			if (it->revents != 0)
				Logger(basic_type, debug_lvl) << "FD " << it->fd << " revent: " << it->revents;
			if (_event_handler_table->find(it->fd) != _event_handler_table->end()) // If fd has been removed from handler table, it should not be inspected
			{					
				try {
					if (POLLIN == (POLLIN & it->revents))	// Important to check POLLIN before POLLHUP: in case of the CGI, POLLHUP happens when cgi process is terminated, but there might still be content to read in the pipe.
					{
						Logger(basic_type, debug_lvl) << "FD " << it->fd << " ready for reading";
						_event_handler_table->get(it->fd)->readable();
					}
					else if (((POLLHUP | POLLERR) & it->revents) > 0)
					{
						Logger(basic_type, debug_lvl) << "Client socket disconnected";
						remove_handle(it->fd);
					}
					else if (POLLOUT == (POLLOUT & it->revents))
					{
						Logger(basic_type, debug_lvl) << "FD " << it->fd << " ready for writing";
						_event_handler_table->get(it->fd)->writable();
						// it->events = POLLIN;
					}
					else if (_event_handler_table->get(it->fd)->is_timeoutable())
					{
						if (_event_handler_table->get(it->fd)->is_timeout())	//Only client handlers can timeout for now
						{
							Logger(basic_type, debug_lvl) << "Fd " << it->fd << " timed out";
							remove_handle(it->fd);
						}
					}
				}
				catch (const ClientException & e)
				{
					remove_handle(e.getfd());
					Logger(basic_type, error_lvl) << e.what() << ' ' << it->fd;
				}	
				catch (const ClientSystemException & e)
				{
					remove_handle(e.getfd());
					Logger(error_type, error_lvl) << e.what() << ' ' << it->fd;
				}
				catch (const ServerSystemException & e)
				{
					Logger(error_type, error_lvl) << e.what() << ' ' << it->fd;
					return ;
				}
				catch (const Exception & e)
				{
					Logger(basic_type, debug_lvl) << e.what() << ' ' << it->fd;
				}
				catch (const SystemException & e)
				{
					remove_handle(it->fd);
					Logger(error_type, error_lvl) << e.what();
				}
			}
		}
	}
	Logger(basic_type, debug_lvl) << "Leaving main loop handle_events";
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
InitiationDispatcher::add_read_handle(size_t file_size, Response & resp)
{
	ReadHandler *rh = new ReadHandler(file_size, resp);
	_event_handler_table->add(resp.get_handler_fd(), *rh);
}

void
InitiationDispatcher::add_write_handle(const std::vector<char> & body, Response & resp)
{
	WriteHandler *wh = new WriteHandler(body, resp);
	_event_handler_table->add(resp.get_handler_fd(), *wh);
}

void
InitiationDispatcher::add_cgi_handle(Request & req, Response & resp, int open_pipe[2], const std::string & method)
{
	CgiHandler *ch = new CgiHandler(req, resp, open_pipe, method);
	_event_handler_table->add(resp.get_handler_fd(), *ch);
}

void
InitiationDispatcher::remove_handle(int fd)
{
	Logger(basic_type, debug_lvl) << "Call to remove FD: " << fd;
	_event_handler_table->remove(fd);
	Logger(basic_type, debug_lvl) << "FD " << fd << " removed";
}
