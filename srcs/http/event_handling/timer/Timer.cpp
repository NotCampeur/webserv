#include "Timer.hpp"

Timer::Timer(time_t timeout) :
_timeout(timeout)
{
	reset();
}

Timer::Timer(Timer const & src) :
_sec(src._sec),
_timeout(src._timeout)
{}

Timer::~Timer(void) {}

void
Timer::reset(void)
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	_sec = tp.tv_sec;
}

bool
Timer::expired(void) const
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	if ((tv.tv_sec - _sec) >= _timeout)
		return true;
	return false;
}
