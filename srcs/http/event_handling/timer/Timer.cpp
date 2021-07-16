#include "Timer.hpp"

Timer::Timer(void)
{
	reset();
}

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

	if ((tv.tv_sec - _sec) >= CLIENT_TIMEOUT)
		return true;
	return false;
}
