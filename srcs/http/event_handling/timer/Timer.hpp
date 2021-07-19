#ifndef WEBSERV_timer_H
# define WEBSERV_timer_H

# include "webserv.hpp"

class Timer
{
	private:
		time_t			_sec;
		const time_t	_timeout;

	public:

		Timer(time_t timeout);
		Timer(Timer const & src);
		~Timer(void);

		void	reset(void);
		bool	expired(void) const;

};

#endif
