#ifndef DEMULTIPLEXOR
# define DEMULTIPLEXOR

class demultiplexer
{
    private:


    public:

        typedef int demultiplex_ret_type;

        demultiplexer(void);
        demultiplexer(demultiplexer const & src);
        ~demultiplexer(void);

        demultiplexer &  operator=(demultiplexer const & src);

        demultiplex_ret_type demultiplex(void);
};

#endif