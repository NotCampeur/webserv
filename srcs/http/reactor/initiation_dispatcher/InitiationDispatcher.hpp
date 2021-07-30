#ifndef WEBSERV_INITIATION_DISPATCHER_HPP
# define WEBSERV_INITIATION_DISPATCHER_HPP

# include "Demultiplexer.hpp"
# include "HandlerTable.hpp"
# include "ClientHandler.hpp"
# include "ServerHandler.hpp"
# include "ReadHandler.hpp"
# include "WriteHandler.hpp"
# include "Exception.hpp"
# include "SystemException.hpp"
# include "ServerSystemException.hpp"
# include "ClientSystemException.hpp"
# include "Singleton.hpp"

class Request;
class Response;

class InitiationDispatcher : public Singleton<InitiationDispatcher>
{
	private:
		Demultiplexer		* const _demultiplexer;
		HandlerTable		* const _event_handler_table;

	public:
		InitiationDispatcher(void);
		~InitiationDispatcher(void);

		// Main loop: calls the demultiplexor and handle events based on demultiplexor output
		void					handle_events(void);
		void					add_server_handle(const Server & srv);
		void					add_client_handle(const Client & clt);
		void					add_read_handle(size_t file_size, Response & resp);
		void					add_write_handle(const std::string & body, Response & resp);
		void					remove_handle(int fd);

	private:
		InitiationDispatcher(const InitiationDispatcher & src);
		InitiationDispatcher &	operator=(const InitiationDispatcher & src);

		void					set_demultiplexer_handles(void);
};

#endif