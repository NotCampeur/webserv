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
	Logger(LOG_FILE, basic_type, debug_lvl) << "Handler table contains " << _handler_table->size() << " elements";
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
		Logger(LOG_FILE, basic_type, debug_lvl) << "Handler table: " << _handler_table->size() << "  IEventHandler elements deleted";
	}
	delete _handler_table;
	Logger(LOG_FILE, basic_type, minor_lvl) << "Handler Table has been destroyed";
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
	Logger(LOG_FILE, basic_type, debug_lvl) << "fd: " << fd << " has been add to the handler table";
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
