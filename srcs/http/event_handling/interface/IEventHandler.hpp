#ifndef WEBSERV_EVENTHANDLER_HPP
# define WEBSERV_EVENTHANDLER_HPP

class IEventHandler
{
    public:
		virtual	~IEventHandler() {}

    virtual int		readable(void) = 0;
    virtual void	writable(void) = 0;
	virtual	bool	is_timeoutable(void) = 0;
	virtual bool	is_timeout(void) = 0;

};

#endif