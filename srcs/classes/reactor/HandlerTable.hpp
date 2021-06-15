#ifndef HANDLERTABLE_H
# define HANDLERTABLE_H

# include "webserv.hpp"
# include "IEventHandler.hpp"

// Table holding handles (fds) and associated event handler object
// Implemented using map container

class HandlerTable
{
	public:

		typedef std::map<int, IEventHandler *>	table_type;

	private:

		table_type *					_handler_table;
	
	public:

		HandlerTable(void);
		HandlerTable(const HandlerTable & src);
		~HandlerTable(void);

		void			add(int fd, IEventHandler & event_handler);
		void			remove(int fd);
		IEventHandler *	get(int fd) const;
		
		HandlerTable &	operator=(const HandlerTable & src);
};

#endif
