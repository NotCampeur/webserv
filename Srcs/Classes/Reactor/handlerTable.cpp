#include "HandlerTable.hpp"

HandlerTable::HandlerTable(void) : _handler_table(new table_type [0])
{}

HandlerTable::HandlerTable(const HandlerTable & src)
{
    *(this->_handler_table) = std::map(*src._handler_table);
}

HandlerTable::~HandlerTable(void)
{
    delete [] this->_handler_table;
}

HandlerTable &
HandlerTable::operator=(const HandlerTable & src)
{
    HandlerTable ht(src);
    return ht;
}

void
HandlerTable::add(int fd, IEventHandler & event_handler)
{
    this->_handler_table->insert(std::pair<int, IEventHandler *>(fd, &event_handler));
}

void
HandlerTable::remove(int fd)
{
    this->_handler_table->erase(fd);
}

IEventHandler *
HandlerTable::get(int fd) const
{
    return (*this->_handler_table->find(fd)).second;
}