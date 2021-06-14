#include "HandlerTable.hpp"

HandlerTable::HandlerTable(void)
: _handler_table(new table_type), _demultiplexer_fds(NULL)
{}

HandlerTable::HandlerTable(const HandlerTable & src)
{
	*this = src;
}

HandlerTable::~HandlerTable(void)
{
	if (!_handler_table->empty())
	{
		table_type::iterator it = _handler_table->begin();
		table_type::iterator ite = _handler_table->end();

		for (;it != ite; it++)
		{
			delete it->second;
		}
	}
	delete _handler_table;
}

void
HandlerTable::set_demultiplexer_fds(std::vector<struct pollfd> * fds_address)
{
	if (_demultiplexer_fds == NULL)
		_demultiplexer_fds = fds_address;
}

HandlerTable &
HandlerTable::operator=(const HandlerTable & src)
{
	if (this != &src)
	{
		_handler_table = src._handler_table;
		_demultiplexer_fds = src._demultiplexer_fds;
	}
	return *this;
}

void
HandlerTable::add(int fd, IEventHandler & event_handler)
{
	_handler_table->insert(std::pair<int, IEventHandler *>(fd, &event_handler));
	#ifdef DEBUG
		std::cout << "fd: " << fd << " has been add to the handler table";
	#endif
	if (_demultiplexer_fds != NULL)
	{
		struct pollfd	fd_data;

		fd_data.fd = fd;
		fd_data.events = POLLIN | POLLOUT;
		fd_data.revents = 0;
		_demultiplexer_fds->push_back(fd_data);
		#ifdef DEBUG
			std::cout << " and to the demultiplexer";
		#endif
	}
	#ifdef DEBUG
		std::cout << std::endl;
	#endif
}

void
HandlerTable::remove(int fd)
{
	delete _handler_table->find(fd)->second;
	_handler_table->erase(fd);
	#ifdef DEBUG
		std::cout << "fd: " << fd << " has been removed from the handler table";
	#endif
	if (_demultiplexer_fds != NULL)
	{
		_demultiplexer_fds->erase(std::find(_demultiplexer_fds->begin(), _demultiplexer_fds->end(), fd));
		#ifdef DEBUG
			std::cout << " and from the demultiplexer";
		#endif
	}
	#ifdef DEBUG
		std::cout << std::endl;
	#endif
}

IEventHandler *
HandlerTable::get(int fd) const
{
	return (*_handler_table->find(fd)).second;
}

HandlerTable::table_type &
HandlerTable::handler_table(void) const
{
	return *_handler_table;
}

bool	operator==(struct pollfd to_look, int to_find)
{
	if (to_look.fd == to_find)
		return true;
	return false;
}
