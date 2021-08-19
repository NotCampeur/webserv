#ifndef WEBSERV_READHANDLER_HPP
# define WEBSERV_READHANDLER_HPP

# include "IEventHandler.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Environment.hpp"

class CgiHandler : public IEventHandler
{
	private:
		const Request &			_request;
		Response &				_response;
		int						_event_flag;
		Environment				_env;

	public:

		CgiHandler(const Request & req, Response & resp);
		~CgiHandler(void);

		virtual void	readable(void);
		virtual void	writable(void);
		virtual	bool	is_timeoutable(void) const;
		virtual bool	is_timeout(void) const;
		virtual int		get_event_flag(void) const;

	private:
		CgiHandler(CgiHandler const & src);
		void	set_environment(void);

};

#endif
