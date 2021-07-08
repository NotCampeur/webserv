#include "ServerHandler.hpp"

ServerHandler::ServerHandler(const Server * server, InitiationDispatcher & idis) :
_server(*server),
_idis(idis),
_event_flag(POLLIN)
{}


ServerHandler::~ServerHandler(void)
{
	delete &_server;
}

ServerHandler &
ServerHandler::operator=(ServerHandler const & src)
{
	(void)src;
    // Cannot copy const value, remove operator?
    return *this;
}

void
ServerHandler::readable(void)
{
	socklen_t sockaddr_size = sizeof(struct sockaddr);

	while (1)
	{
		struct sockaddr * address = new (struct sockaddr);
		int ret = accept(get_serverfd(), address, &sockaddr_size);

		if (ret >= 0)
		{
			if (fcntl(ret, F_SETFL, O_NONBLOCK) < 0)
				throw SYSException("Unable to set nonblocking flag on fd");

			Client * client = new Client(ret, address);

			Logger(LOG_FILE, basic_type, minor_lvl) << "A new connection has been accepted on fd : " << ret;
			_idis.add_handle(*client);
		}
		else
		{
			delete address;
			if (errno != EWOULDBLOCK)
				throw SYSException("Accept error");
			Logger(LOG_FILE, basic_type, debug_lvl) << "Accept backlog of " << _server.getsockfd() << " is empty";
			break ;
		}
	}
}

// No writable action can be detected on a server socket, hence this function does not do anything
void
ServerHandler::writable(void)
{}

bool
ServerHandler::is_timeoutable(void) const
{
	return false;
}

bool
ServerHandler::is_timeout(void) const
{
	return false;
}

int
ServerHandler::get_event_flag(void) const
{
	return _event_flag;
}

int
ServerHandler::get_serverfd(void) const
{
    return _server.getsockfd();
}

// const char *
// ServerHandler::UnableToAcceptConnection::what() const throw()
// {
// 	std::ostringstream oss;
// 	oss << "Accept error: " << _error << " : errno : " << strerror(errno) << std::endl;
	
// 	return oss.str().c_str();
// }

// ServerHandler::UnableToSetNonblockFlag::UnableToSetNonblockFlag() throw()
// : _msg("cannot set nonblocking flag on fd"), _fd(-1)
// {
// 	_msg << " : " << strerror(errno);
// }

// ServerHandler::UnableToSetNonblockFlag::UnableToSetNonblockFlag(int fd) throw()
// : _msg("cannot set nonblocking flag on fd : "), _fd(fd)
// {
// 	_msg << _fd << " : " << strerror(errno);
// }

// ServerHandler::UnableToSetNonblockFlag::UnableToSetNonblockFlag(const UnableToSetNonblockFlag & to_copy) throw()
// {
// 	_fd = to_copy._fd;
// 	_msg << to_copy._msg.str();
// }

// ServerHandler::UnableToSetNonblockFlag::~UnableToSetNonblockFlag() throw()
// {}

// const char *
// ServerHandler::UnableToSetNonblockFlag::what() const throw()
// {
// 	return _msg.str().c_str();
// }