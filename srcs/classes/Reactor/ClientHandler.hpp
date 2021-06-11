#ifndef CLIENTHANDLER_H
# define CLIENTHANDLER_H

# include "IEventHandler.hpp"
# include "HandlerTable.hpp"
# include "Client.hpp"


class ClientHandler : public IEventHandler
{
	private:

		const Client &	_client;
		HandlerTable &	_ht;

	public:

		ClientHandler(const Client & client, HandlerTable & ht);
		ClientHandler(ClientHandler const & src);
		~ClientHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);

		int			 get_clientfd(void) const;

	private:
		void	send_header(size_t content_length);
	// Exceptions
	public:

		class UnableToReadClientRequest : public std::exception
		{
			const char *what() const throw();
		};
		
		class UnableToWriteToClient : public std::exception
		{
			const char *what() const throw();
		};
};

#endif
