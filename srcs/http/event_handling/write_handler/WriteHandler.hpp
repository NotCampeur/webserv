#ifndef WEBSERV_WRITEHANDLER_HPP
# define WEBSERV_WRITEHANDLER_HPP

# include "IEventHandler.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Timer.hpp"
# include "SYSException.hpp"
# include "HttpException.hpp"

class WriteHandler : public IEventHandler
{
	private:

		const Client &			_client;
		Request					_request;
		Response				_response;
		RequestParser			_req_parser;
		Timer					_timer;
		const int				_event_flag;

	public:

		WriteHandler(const std::string & body, Response & resp);
		~WriteHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

	private:
		WriteHandler(WriteHandler const & src);
		void	handle_http_error(void);
		// void	set_header(std::stringstream & header, size_t content_length);
};

#endif
