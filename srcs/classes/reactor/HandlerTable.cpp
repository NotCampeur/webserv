#include "HandlerTable.hpp"

HandlerTable::HandlerTable(void)
: _handler_table(new table_type)
{}

HandlerTable::HandlerTable(const HandlerTable & src)
{
	*this = src;
}

HandlerTable::~HandlerTable(void)
{
	std::ostringstream	nb;
	nb << _handler_table->size();
	Logger() << "Handler table contains " + nb.str() + " elements";
	if (!_handler_table->empty())
	{
		table_type::iterator it = _handler_table->begin();
		table_type::iterator ite = _handler_table->end();

		int i = 0;
		for (;it != ite; it++)
		{
			delete it->second;
			i++;
		}
		std::ostringstream	nb;
		nb << i;
		Logger() << "Handler table: " + nb.str() + "  IEventHandler elements deleted";
	}
	delete _handler_table;
	Logger() << "Handler Table has been destroyed";
}

HandlerTable &
HandlerTable::operator=(const HandlerTable & src)
{
	if (this != &src)
		_handler_table = src._handler_table;
	return *this;
}

void
HandlerTable::add(int fd, IEventHandler & event_handler)
{
	_handler_table->insert(std::pair<int, IEventHandler *>(fd, &event_handler));
	std::ostringstream	nb;
	nb << fd;
	Logger() << "fd: " + nb.str() + " has been add to the handler table";
}

void
HandlerTable::remove(int fd)
{
	delete _handler_table->find(fd)->second;
	_handler_table->erase(fd);
	std::ostringstream	nb;
	nb << fd;
	Logger() << "fd: " + nb.str() + " has been removed from the handler table";
}

IEventHandler *
HandlerTable::get(int fd) const
{
	return (*_handler_table->find(fd)).second;
}
