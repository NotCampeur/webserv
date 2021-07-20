#ifndef WEBSERV_READHANDLER_HPP
# define WEBSERV_READHANDLER_HPP

# include "IEventHandler.hpp"
# include "Response.hpp"

class ReadHandler : public IEventHandler
{
	private:
		const int				_fd;
		size_t					_file_size;
		Response &				_response;
		int						_event_flag;
		size_t					_bytes_read;

	public:

		ReadHandler(int fd, size_t file_size, Response & resp);
		~ReadHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

	private:
		ReadHandler(ReadHandler const & src);
		void	manage_error(void);
		void	response_complete(void);
};

#endif
