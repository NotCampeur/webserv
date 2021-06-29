#ifndef WEBSERV_SERVER_HANDLER_HPP
# define WEBSERV_SERVER_HANDLER_HPP

# include "IEventHandler.hpp"
# include "Server.hpp"
# include "Client.hpp"

class InitiationDispatcher;
# include "InitiationDispatcher.hpp"

class ServerHandler : public IEventHandler
{
    private:

        const Server &          _server;
        InitiationDispatcher &  _idis;

    public:

        ServerHandler(const Server * server, InitiationDispatcher & idis);
        ServerHandler(ServerHandler const & src);
        ~ServerHandler(void);

        ServerHandler &  operator=(ServerHandler const & src);

        virtual int		readable(void);
        virtual void	writable(void);

        int             get_serverfd(void) const;

    private:

        ServerHandler(void);    // Default constructor
        void    new_client_handler(Client & client);

    // Exceptions
    public:

        class UnableToAcceptConnection : public std::exception
		{
			public:
				UnableToAcceptConnection(int error) throw() : _error(error) {}
			private:
				const char *what() const throw();
				int			_error;
		};
};

#endif
