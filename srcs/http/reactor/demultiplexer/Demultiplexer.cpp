#include "Demultiplexer.hpp"

Demultiplexer::Demultiplexer(int timeout) :
_timeout(timeout)
{}

Demultiplexer::Demultiplexer(const Demultiplexer & src) :
_pollfds(src._pollfds),
_timeout(src._timeout)
{}

Demultiplexer::~Demultiplexer(void)
{}

Demultiplexer &
Demultiplexer::operator=(const Demultiplexer & src)
{
	_pollfds = src._pollfds;
	_timeout = src._timeout;
	return *this;
}

int
Demultiplexer::activate()
{
	int	result = 0;

	result = poll(&_pollfds[0], _pollfds.size(), _timeout);
	if (result == -1)
	{
		throw SystemException("Unable to poll descriptors");
	}
	else if (result == 0)
	{
		Logger(LOG_FILE, basic_type, minor_lvl) << "Poll timeout";
		return result;
	}
	std::ostringstream	nb;
	nb << result;
	Logger(LOG_FILE, basic_type, major_lvl) << nb.str() + " fd ready";
	return result;
}

void
Demultiplexer::addfd(int fd, int flag)
{
	struct pollfd	fd_data;

	fd_data.fd = fd;
	fd_data.events = flag;
	fd_data.revents = 0;
	_pollfds.push_back(fd_data);
	Logger(LOG_FILE, basic_type, minor_lvl) << "fd: " << fd << " has been added to demultiplexer";
}

void
Demultiplexer::removefd(int fd)
{
	if (!_pollfds.empty())
	{
		pollfd_arr::iterator it = _pollfds.begin();
		pollfd_arr::iterator ite = _pollfds.end();
		for (; it != ite; it++)
		{
			if (it->fd == fd)
			{
				_pollfds.erase(it);
				Logger(LOG_FILE, basic_type, minor_lvl) << "fd: " << fd << " removed from pollfd array";
				return ;
			}
		}
	}
	throw Exception("Fd not found");
}

void					
Demultiplexer::clear(void)
{
	_pollfds.clear();
}

Demultiplexer::pollfd_arr::iterator
Demultiplexer::begin()
{
	return _pollfds.begin();
}

Demultiplexer::pollfd_arr::iterator
Demultiplexer::end()
{
	return _pollfds.end();
}