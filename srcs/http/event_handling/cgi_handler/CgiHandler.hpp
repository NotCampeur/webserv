#ifndef WEBSERV_CGIHANDLER_HPP
# define WEBSERV_CGIHANDLER_HPP

# include "IEventHandler.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Environment.hpp"
# include "CgiParser.hpp"

class CgiHandler : public IEventHandler
{
	private:
		Request &				_request;
		Response &				_response;
		const std::string		_method;
		std::string				_file_ext;
		int						_pipe_fd[2];
		int						_event_flag;
		Environment				_env;
		int						_pid;
		ssize_t					_written_size;
		bool					_cgi_done;
		CgiParser				_parser;


	public:

		CgiHandler(Request & req, Response & resp, std::string method);
		~CgiHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

		int				get_fd(void) const;
		void			start_cgi();

	private:
		CgiHandler(CgiHandler const & src);
		void	set_environment(void);
		void	manage_error(void);
		void	make_complete(void);
		bool	cgi_process_error(void);

};

#endif
