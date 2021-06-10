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
	struct pollfd	*fd_data;

	for(; it != end; ++it)
	{
		fd_data = new struct pollfd;
		memset(fd_data, 0, sizeof(struct pollfd));
		fd_data->fd = it->first;
		fd_data->events = POLLIN | POLLOUT;
		_fds.push_back(fd_data);
		#ifdef DEBUG
			std::cout << "fd: " << it->first << " has been add to demultiplexer" << std::endl;
		#endif
	}
}

Demultiplexer::~Demultiplexer(void)
{
	std::vector<struct pollfd *>::iterator	it = _fds.begin();
	std::vector<struct pollfd *>::iterator	end = _fds.end();

	for (; it != end; ++it)
		delete *it;
	#ifdef DEBUG
		std::cout << "Demultiplexer has been destroyed" << std::endl;
	#endif
}

Demultiplexer &
Demultiplexer::operator=(const Demultiplexer & src)
{
    return *this;
}

int
Demultiplexer::activate(void)
{
	int	result(0);

	result = poll(*_fds.data(), _fds.size(), _timeout);
	if (result == -1)
		throw Demultiplexer::PollingError();
	else if (result == 0)
		throw Demultiplexer::PollingTimeout();
	return result;
}

void
Demultiplexer::add(int fd)
{
	struct pollfd	*fd_data;

	fd_data = new struct pollfd;
	memset(fd_data, 0, sizeof(struct pollfd));
	fd_data->fd = fd;
	fd_data->events = POLLIN | POLLOUT;
	_fds.push_back(fd_data);
	#ifdef DEBUG
		std::cout << "fd: " << fd << " has been add to demultiplexer" << std::endl;
	#endif
}

void
Demultiplexer::remove(int fd)
{
	std::vector<struct pollfd *>::iterator	it = _fds.begin();
	std::vector<struct pollfd *>::iterator	end = _fds.end();

	for (; it != end; ++it)
		if ((*it)->fd == fd)
		{
			_fds.erase(it);
			#ifdef DEBUG
				std::cout << "fd : " << fd << " has been removed" << std::endl;
			#endif
			return ;
		}
}

std::vector<int> &
Demultiplexer::getReadables(void)
{
	std::vector<int> result;
	std::vector<struct pollfd *>::iterator	it = _fds.begin();
	std::vector<struct pollfd *>::iterator	end = _fds.end();

	for (; it != end; ++it)
		if ((*it)->revents == POLLIN)
			result.push_back((*it)->fd);
	return result;
}

std::vector<int> &
Demultiplexer::getWritables(void)
{
	std::vector<int> result;
	std::vector<struct pollfd *>::iterator	it = _fds.begin();
	std::vector<struct pollfd *>::iterator	end = _fds.end();

	for (; it != end; ++it)
		if ((*it)->revents == POLLOUT)
			result.push_back((*it)->fd);
	return result;
}

const char *
Demultiplexer::PollingError::what(void) const
{
	return (std::string(std::string("Unable to poll descriptors : ")
			+ std::string(strerror(errno))).c_str());
}

const char *
Demultiplexer::PollingTimeout::what(void) const
{
	return (std::string("The polling timeout : ").c_str());
}