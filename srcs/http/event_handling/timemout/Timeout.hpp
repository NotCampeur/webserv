#ifndef WEBSERV_TIMEOUT_H
# define WEBSERV_TIMEOUT_H

# include "webserv.hpp"

class Timeout
{
	private:
		time_t	_sec;

	public:

		Timeout(void);
		~Timeout(void);

		void	reset(void);
		bool	expired(void) const;

};

#endif
