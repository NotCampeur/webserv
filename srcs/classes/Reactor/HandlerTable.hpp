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

		HandlerTable(void);
		HandlerTable(const HandlerTable & src);
		~HandlerTable(void);

		void	set_demultiplexer_fds(std::vector<struct pollfd> * fds_address);
		void	add(int fd, IEventHandler & event_handler);
		void	remove(int fd);

		IEventHandler *	get(int fd) const;
		
		table_type &	handler_table(void) const;

		HandlerTable &	operator=(const HandlerTable & src);

	private:
		table_type *					_handler_table;
		std::vector<struct pollfd> *	_demultiplexer_fds;
};

bool		operator==(struct pollfd to_look, int to_find);

#endif
