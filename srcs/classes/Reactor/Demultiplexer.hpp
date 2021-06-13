#ifndef DEMULTIPLEXER
# define DEMULTIPLEXER

# include "webserv.hpp"
# include "HandlerTable.hpp"

class Demultiplexer
{
	public:
		typedef std::vector<struct pollfd>	fd_type;

	private:
		fd_type	_fds;
		int		_timeout;

		Demultiplexer(void);

	public:
		// Demultiplexer(HandlerTable & table, int timeout = DEMULTIMPEXER_TIMEOUT);
		Demultiplexer(int timeout = DEMULTIMPEXER_TIMEOUT);		
		Demultiplexer(const Demultiplexer & src);
		~Demultiplexer(void);
		
		Demultiplexer & operator=(const Demultiplexer & src);

		//	Will poll every fd to get tag the Writable | Readable ones.
		int		activate(void);

		fd_type	&	getfds(void) const;
		void		addfd(int fd);
		void		removefd(int fd);

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
