#ifndef WEBSERV_EVENTHANDLER_HPP
# define WEBSERV_EVENTHANDLER_HPP

class IEventHandler
{
    public:
		virtual	~IEventHandler() {}

    virtual void	readable(void) = 0;
    virtual void	writable(void) = 0;
	virtual	bool	is_timeoutable(void) const = 0;
	virtual bool	is_timeout(void) const = 0;
	virtual int		get_event_flag(void) const = 0;
};

#endif