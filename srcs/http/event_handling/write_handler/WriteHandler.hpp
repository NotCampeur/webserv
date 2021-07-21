#ifndef WEBSERV_WRITEHANDLER_HPP
# define WEBSERV_WRITEHANDLER_HPP

# include "IEventHandler.hpp"
# include "Response.hpp"
# include "Mime.hpp"

class WriteHandler : public IEventHandler
{
	private:
		int						_fd;
		const std::string &		_body;
		Response				_response;
		int						_event_flag;
		size_t					_bytes_written;

	public:

		WriteHandler(int fd, const std::string & body, Response & resp);
		~WriteHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

	private:
		WriteHandler(WriteHandler const & src);
		void	response_complete(void);
		void	manage_error(void);
};

#endif
