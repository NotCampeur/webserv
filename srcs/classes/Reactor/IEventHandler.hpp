#ifndef EVENTHANDLER_H
# define EVENTHANDLER_H

class IEventHandler
{
    public:
		virtual	~IEventHandler() {}

        virtual void readable(void) = 0;
        virtual void writable(void) = 0;
};

#endif