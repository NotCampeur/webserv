#ifndef CLIENTHANDLER_H
# define CLIENTHANDLER_H

# include "IEventHandler.hpp"
# include "HandlerTable.hpp"
// include path tbu
# include "../client/Client.hpp"


class ClientHandler : public IEventHandler
{
    private:

        const Client &    _client;
        HandlerTable &    _ht;

    public:

        ClientHandler(const Client & client, HandlerTable & ht);
        ClientHandler(ClientHandler const & src);
        ~ClientHandler(void);

        ClientHandler &  operator=(ClientHandler const & src);


        virtual void    readable(void);
        virtual void    writable(void);

        int             getfd(void) const;

    private:

        ClientHandler(void);    // Default constructor

    // Exceptions
    public:

    	class UnableToGetClientRequest : public std::exception
		{
				const char *what() const throw();
		};
};

#endif
