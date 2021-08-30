#ifndef WEBSERV_DEMULTIPLEXER_HPP
# define WEBSERV_DEMULTIPLEXER_HPP

# include "webserv.hpp"
# include "HandlerTable.hpp"
# include "SystemException.hpp"
# include "Exception.hpp"

class Demultiplexer
{
	public:
		typedef std::vector<struct pollfd>	pollfd_arr;

	private:
		pollfd_arr	_pollfds;
		int			_timeout;

	public:
		Demultiplexer(int timeout = DEMULTIMPEXER_TIMEOUT);		
		Demultiplexer(const Demultiplexer & src);
		~Demultiplexer(void);
		
		Demultiplexer & operator=(const Demultiplexer & src);

		int						activate();
		void					addfd(int fd, int flag);
		void					removefd(int fd);
		void					clear(void);
		pollfd_arr::iterator	begin();
		pollfd_arr::iterator	end();
};

#endif
