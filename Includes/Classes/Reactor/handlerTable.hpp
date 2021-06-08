#ifndef HANDLERTABLE_H
# define HANDLERTABLE_H

# include "IeventHandler.hpp"
# include <map>
# include <vector>

class handlerTable
{

public:

    typedef int handle_type;
    typedef typename std::map<handle_type, IeventHandler>    table_type;

    handlerTable(void);
    handlerTable(handlerTable const & src);
    ~handlerTable(void);

    void add(handle_type handle, IeventHandler & event_handler);
    void delete(handle_type h_val);
    IeventHandler & get_handler(handle_type h_val);

    handlerTable &  operator=(handlerTable const & src);

private:
    table_type *_handler_table;

};

#endif
