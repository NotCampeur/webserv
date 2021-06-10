#ifndef HANDLERTABLE_H
# define HANDLERTABLE_H

# include "IEventHandler.hpp"
# include <map>

// Table holding handles (fds) and associated event handler object
// Implemented using map container

class HandlerTable
{

public:

    typedef typename std::map<int, IEventHandler *>    table_type;

    HandlerTable(void);
    HandlerTable(const HandlerTable & src);
    ~HandlerTable(void);

    void add(int fd, IEventHandler & event_handler);
    void remove(int fd);
    IEventHandler * get(int fd) const;
	table_type & handler_table(void) const;


    HandlerTable &  operator=(const HandlerTable & src);

private:
    table_type *_handler_table;

};

#endif
