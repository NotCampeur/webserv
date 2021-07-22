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
	}
	delete _handler_table;
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
	Logger(LOG_FILE, basic_type, debug_lvl) << "fd: " << fd << " has been added to the handler table";
}

void
HandlerTable::remove(int fd)
{
	delete _handler_table->find(fd)->second;
	_handler_table->erase(fd);
	Logger(LOG_FILE, basic_type, debug_lvl) << "fd: " << fd << " has been removed from the handler table";
}

IEventHandler *
HandlerTable::get(int fd) const
{
	return (*_handler_table->find(fd)).second;
}

size_t
HandlerTable::size(void) const
{
	return _handler_table->size();
}


HandlerTable::iterator
HandlerTable::begin(void) const
{
	return _handler_table->begin();
}

HandlerTable::iterator
HandlerTable::end(void) const
{
	return _handler_table->end();
}

HandlerTable::iterator
HandlerTable::find(int fd) const
{
	return _handler_table->find(fd);
}