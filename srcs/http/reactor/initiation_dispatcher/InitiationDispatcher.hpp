#ifndef WEBSERV_INITIATION_DISPATCHER_HPP
# define WEBSERV_INITIATION_DISPATCHER_HPP

# include "Demultiplexer.hpp"
# include "HandlerTable.hpp"
# include "Singleton.hpp"
class Server;
class Client;
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
		void					add_write_handle(const std::vector<char> & body, Response & resp);
		void					add_cgi_handle(Request & req, Response & resp, int open_pipe[2], const std::string & method);
		void					remove_handle(int fd);

	private:
		InitiationDispatcher(const InitiationDispatcher & src);
		InitiationDispatcher &	operator=(const InitiationDispatcher & src);

		void					set_demultiplexer_handles(void);
};

#endif