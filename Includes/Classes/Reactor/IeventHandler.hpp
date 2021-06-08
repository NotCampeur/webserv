#ifndef EVENTHANDLER_H
# define EVENTHANDLER_H

class IeventHandler
{
    public:

        virtual void write_event(void) = 0;
        virtual void read_event(void) = 0;
        virtual void get_handle(void) const = 0;
};

#endif