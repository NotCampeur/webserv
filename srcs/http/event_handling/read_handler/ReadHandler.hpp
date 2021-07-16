#ifndef WEBSERV_READHANDLER_HPP
# define WEBSERV_READHANDLER_HPP

# include "IEventHandler.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Timer.hpp"
# include "SYSException.hpp"
# include "HttpException.hpp"

class ReadHandler : public IEventHandler
{
	private:
		const int				_fd;
		Response &				_response;
		Timer					_timer;
		const int				_event_flag;

	public:

		ReadHandler(int fd, Response & resp);
		~ReadHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

	private:
		ReadHandler(ReadHandler const & src);
		void	handle_http_error(void);
		// void	set_header(std::stringstream & header, size_t content_length);
};

#endif
