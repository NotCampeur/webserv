#ifndef WEBSERV_CLIENT_HANDLER_HPP
# define WEBSERV_CLIENT_HANDLER_HPP

# include "IEventHandler.hpp"
# include "Client.hpp"
# include "RequestParser.hpp"
# include "Timeout.hpp"

class ClientHandler : public IEventHandler
{
	private:

		const Client &			_client;
		RequestParser			_req_parser;
		Timeout					_timeout;
		int						_event_flag;

	public:

		ClientHandler(const Client & client);
		ClientHandler(ClientHandler const & src);
		~ClientHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

		int				get_clientfd(void) const;


	private:
		void	set_header(std::stringstream & header, size_t content_length);
	
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

		class BadEventFrag : public std::exception
		{
			const char *	what(void) const throw();
		};

		class ClientClosedConnection : public std::exception
		{
			public:
				const char *	what(void) const throw();
		};
};

#endif
