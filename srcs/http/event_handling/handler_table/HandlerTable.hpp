#ifndef WEBSERV_HANDLERTABLE_HPP
# define WEBSERV_HANDLERTABLE_HPP

# include "webserv.hpp"
# include "IEventHandler.hpp"
# include "Exception.hpp"
// Table holding handles (fds) and associated event handler object
// Implemented using map container

class HandlerTable
{
	public:

		typedef std::map<int, IEventHandler *>				table_type;
		typedef std::map<int, IEventHandler *>::iterator	iterator;

	private:

		table_type *					_handler_table;
	
	public:

		HandlerTable(void);
		HandlerTable(const HandlerTable & src);
		~HandlerTable(void);

		void			add(int fd, IEventHandler & event_handler);
		void			remove(int fd);
		iterator		begin(void) const;
		iterator		end(void) const;
		iterator		find(int fd) const;
		IEventHandler *	get(int fd) const;
		size_t			size(void) const;
		
		HandlerTable &	operator=(const HandlerTable & src);
};

#endif
