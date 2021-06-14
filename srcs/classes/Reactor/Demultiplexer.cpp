#include "Demultiplexer.hpp"

Demultiplexer::Demultiplexer(int timeout) :
_timeout(timeout)
{}

Demultiplexer::Demultiplexer(const Demultiplexer & src)
{
    *this = src;
}

Demultiplexer::~Demultiplexer(void)
{
	#ifdef DEBUG
		std::cout << "Demultiplexer has been destroyed" << std::endl;
	#endif
}

Demultiplexer &
Demultiplexer::operator=(const Demultiplexer & src)
{
	if (this != &src)
		_pollfds = src._pollfds;
		_timeout = src._timeout;
	return *this;
}

int
Demultiplexer::activate(void)
{
	int	result(0);

	result = poll(_pollfds.data(), _pollfds.size(), _timeout);
	if (result == -1)
		throw Demultiplexer::PollingError();
	else if (result == 0)
	{
		std::cout << "Poll timeout\n";
		return result;
	}
		// throw Demultiplexer::PollingTimeout();
	#ifdef DEBUG
		std::cout << result << " fd ready." << std::endl;
	#endif
	return result;
}

void
Demultiplexer::addfd(int fd)
{
	struct pollfd	fd_data;

	fd_data.fd = fd;
	fd_data.events = POLLIN | POLLOUT;
	fd_data.revents = 0;

	_pollfds.push_back(fd_data);

		#ifdef DEBUG
			std::cout << "fd: " << fd << " has been added to demultiplexer" << std::endl;
		#endif
}

void
Demultiplexer::removefd(int fd)
{
	if (_pollfds.empty())
		throw Demultiplexer::FdNotFound();
	else
	{
		pollfd_arr::iterator it = _pollfds.begin();
		pollfd_arr::iterator ite = _pollfds.end();
		for (; it != ite; it++)
		{
			if (it->fd == fd)
			{
				_pollfds.erase(it);
					#ifdef DEBUG
						std::cout << "fd " << fd << " removed from pollfd array" << std::endl;
					#endif
				return ;
			}
		}
		throw Demultiplexer::FdNotFound();
	}
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

const char *
Demultiplexer::PollingError::what(void) const throw()
{
	std::string err = "Unable to poll descriptors: ";
	err += strerror(errno);
	return err.c_str();
}

const char *
Demultiplexer::PollingTimeout::what(void) const throw()
{
	return ("The polling timeout.");
}

const char *
Demultiplexer::FdNotFound::what(void) const throw()
{
	return ("Cannot remove fd from pollfds: fd not found");
}