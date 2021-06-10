#ifndef SERVERHANDLER_H
# define SERVERHANDLER_H

# include "IEventHandler.hpp"
# include "HandlerTable.hpp"
# include "ClientHandler.hpp"
// Include paths TBU once makefile is fixed
# include "../Server/Server2.hpp"
# include "../Client/Client.hpp"

class ServerHandler : public IEventHandler
{
    private:

        const Server2 & _server;
        HandlerTable &  _ht;

    public:

        ServerHandler(const Server2 & server, HandlerTable & ht);
        ServerHandler(ServerHandler const & src);
        ~ServerHandler(void);

        ServerHandler &  operator=(ServerHandler const & src);

        virtual void readable(void);
        virtual void writable(void);

        int getfd(void) const;

    private:

        ServerHandler(void);    // Default constructor
        void    new_client_handler(Client & client);

    // Exceptions
    public:

        class AcceptConnectionError : public std::exception
		{
			public:
				AcceptConnectionError(int error) throw() : _error(error) {}
			private:
				const char *what() const throw();
				int			_error;
		};

};

#endif
