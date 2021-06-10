#ifndef DEMULTIPLEXER
# define DEMULTIPLEXER

# include "webserv.hpp"
# include "HandlerTable.hpp"
# include <poll.h>

class Demultiplexer
{
		std::vector<struct pollfd *>	_fds;
		int								_timeout;

		Demultiplexer(void);
		Demultiplexer(const Demultiplexer & src);
		Demultiplexer & operator=(const Demultiplexer & src);

	public:
		Demultiplexer(HandlerTable & table, int timeout = (3 * 60 * 1000));
		~Demultiplexer(void);

		int					activate(void);
		void				add(int	fd);
		void				remove(int fd);

		std::vector<int>	&getReadables(void);
		std::vector<int>	&getWritables(void);

		class PollingError : public std::exception
		{
			const char * what(void) const throw();
		};
		class PollingTimeout : public std::exception
		{
			const char * what(void) const throw();
		};
};

#endif