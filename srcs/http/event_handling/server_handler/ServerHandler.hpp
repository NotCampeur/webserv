#ifndef WEBSERV_SERVER_HANDLER_HPP
# define WEBSERV_SERVER_HANDLER_HPP

# include "IEventHandler.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "SYSException.hpp"

class InitiationDispatcher;
# include "InitiationDispatcher.hpp"

class ServerHandler : public IEventHandler
{
    private:

        const Server &          _server;
        InitiationDispatcher &  _idis;
		int						_event_flag;

    public:

        ServerHandler(const Server * server, InitiationDispatcher & idis);
        ServerHandler(ServerHandler const & src);
        ~ServerHandler(void);

        ServerHandler &  operator=(ServerHandler const & src);

        virtual void	readable(void);
        virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

        int             get_serverfd(void) const;

    private:

        ServerHandler(void);    // Default constructor
        void    new_client_handler(Client & client);

    // Exceptions
    // public:

    //     class UnableToAcceptConnection : public std::exception
	// 	{
	// 		public:
	// 			UnableToAcceptConnection(int error) throw() : _error(error) {}
	// 		private:
	// 			const char *what() const throw();
	// 			int			_error;
	// 	};

	// 	class UnableToSetNonblockFlag : public std::exception
	// 	{
	// 			std::ostringstream	_msg;
	// 			int					_fd;
	// 		public:
	// 			UnableToSetNonblockFlag() throw();
	// 			UnableToSetNonblockFlag(int fd) throw();
	// 			UnableToSetNonblockFlag(const UnableToSetNonblockFlag & to_copy) throw();
	// 			~UnableToSetNonblockFlag() throw();
	// 			const char *what() const throw();
	// 	};
};

#endif
