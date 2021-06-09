#ifndef DEMULTIPLEXER
# define DEMULTIPLEXER

class Demultiplexer
{
    public:

        Demultiplexer(void);
        Demultiplexer(const Demultiplexer & src);
        ~Demultiplexer(void);

        Demultiplexer &  operator=(const Demultiplexer & src);

        int activate(void);
};

#endif