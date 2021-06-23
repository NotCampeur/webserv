#ifndef WEBSERV_CLIENT_HANDLER_HPP
# define WEBSERV_CLIENT_HANDLER_HPP

# include "IEventHandler.hpp"
# include "HandlerTable.hpp"
# include "Client.hpp"


class ClientHandler : public IEventHandler
{
	private:

		const Client &	_client;

	public:

		ClientHandler(const Client & client);
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
				std::string	_msg;
			public:
				UnableToReadClientRequest() throw();
				~UnableToReadClientRequest() throw();
				const char * what(void) const throw();
		};
		
		class UnableToWriteToClient : public std::exception
		{
				std::string	_msg;
			public:
				UnableToWriteToClient() throw();
				~UnableToWriteToClient() throw();
				const char * what(void) const throw();
		};
};

#endif
