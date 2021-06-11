#include "Demultiplexer.hpp"

Demultiplexer::Demultiplexer(void)
{}

Demultiplexer::Demultiplexer(const Demultiplexer & src)
{
    *this = src;
}

Demultiplexer::Demultiplexer(HandlerTable & table, int timeout)
: _timeout(timeout)
{
	HandlerTable::table_type table_map = table.handler_table();
	HandlerTable::table_type::iterator it = table_map.begin();
	HandlerTable::table_type::iterator end = table_map.end();
	struct pollfd	fd_data;

	for(; it != end; ++it)
	{
		fd_data.fd = it->first;
		fd_data.events = POLLIN | POLLOUT;
		fd_data.revents = 0;
		_fds.push_back(fd_data);
		#ifdef DEBUG
			std::cout << "fd: " << it->first << " has been add to demultiplexer" << std::endl;
		#endif
	}
	table.set_demultiplexer_fds(&_fds);
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
		_fds = src._fds;
		_timeout = src._timeout;
	return *this;
}

int
Demultiplexer::activate(void)
{
	int	result(0);

	result = poll(_fds.data(), _fds.size(), _timeout);
	if (result == -1)
		throw Demultiplexer::PollingError();
	else if (result == 0)
		throw Demultiplexer::PollingTimeout();
	#ifdef DEBUG
		std::cout << result << " fd ready." << std::endl;
	#endif
	return result;
}

Demultiplexer::fd_type &
Demultiplexer::fds(void)
{
	return _fds;
}

const char *
Demultiplexer::PollingError::what(void) const throw()
{
	return (std::string(std::string("Unable to poll descriptors : ")
			+ std::string(strerror(errno))).c_str());
}

const char *
Demultiplexer::PollingTimeout::what(void) const throw()
{
	return ("The polling timeout.");
}
