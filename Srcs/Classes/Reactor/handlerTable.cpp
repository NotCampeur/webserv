#include "handlerTable.hpp"

handlerTable::handlerTable(void) : _handler_table(new table_type [0])
{}

handlerTable::handlerTable(handlerTable const & src)
{
    *(this->_handler_table) = std::map(*src._handler_table);
}

handlerTable::~handlerTable(void)
{
    delete [] this->_handler_table;
}

handlerTable &
handlerTable::operator=(handlerTable const & src)
{
    return (*this);
}

void
handlerTable::add(handle_type handle, IeventHandler & event_handler)
{
    
}

void delete(handle_type h_val)
{

}

IeventHandler & get_handler(handle_type h_val)
{
  
};