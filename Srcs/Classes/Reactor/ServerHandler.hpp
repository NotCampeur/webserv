#ifndef SERVERHANDLER_H
# define SERVERHANDLER_H

# include "IEventHandler.hpp"
# include "HandlerTable.hpp"
# include "ClientHandler.hpp"
// Include paths TBU once makefile is fixed
# include "../Server/Server.hpp"
# include "../Client/Client.hpp"

class ServerHandler : public IEventHandler
{
    private:

        const Server & _server;
        HandlerTable &  _ht;

    public:

        ServerHandler(const Server & server, HandlerTable & ht);
        ServerHandler(ServerHandler const & src);
        ~ServerHandler(void);

        ServerHandler &  operator=(ServerHandler const & src);

        virtual void readable(void);
        virtual void writable(void);

        int get_serverfd(void) const;

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
