#include "Timeout.hpp"

Timeout::Timeout(void)
{
	reset();
}

Timeout::~Timeout(void) {}

void
Timeout::reset(void)
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	_sec = tp.tv_sec;
}

bool
Timeout::expired(void) const
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	if ((tv.tv_sec - _sec) >= CLIENT_TIMEOUT)
		return true;
	return false;
}
