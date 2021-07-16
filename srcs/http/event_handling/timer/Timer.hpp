#ifndef WEBSERV_timer_H
# define WEBSERV_timer_H

# include "webserv.hpp"

class Timer
{
	private:
		time_t	_sec;

	public:

		Timer(void);
		~Timer(void);

		void	reset(void);
		bool	expired(void) const;

};

#endif
