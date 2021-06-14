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

		for (;it != ite; it++)
		{
			delete it->second;
		}
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
	#ifdef DEBUG
		std::cout << "fd: " << fd << " has been add to the handler table" << std::endl;
	#endif
}

void
HandlerTable::remove(int fd)
{
	delete _handler_table->find(fd)->second;
	_handler_table->erase(fd);
	#ifdef DEBUG
		std::cout << "fd: " << fd << " has been removed from the handler table" << std::endl;
	#endif
}

IEventHandler *
HandlerTable::get(int fd) const
{
	return (*_handler_table->find(fd)).second;
}