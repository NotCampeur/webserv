#ifndef WEBSERV_EVENTHANDLER_HPP
# define WEBSERV_EVENTHANDLER_HPP

class IEventHandler
{
    public:
		virtual	~IEventHandler() {}

    virtual void readable(void) = 0;
    virtual void writable(void) = 0;
};

#endif