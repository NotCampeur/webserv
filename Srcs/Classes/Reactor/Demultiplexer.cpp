#include "Demultiplexer.hpp"

Demultiplexer::Demultiplexer(void)
{}

Demultiplexer::Demultiplexer(const Demultiplexer & src)
{
    (void)src;
}

Demultiplexer::~Demultiplexer(void)
{}

Demultiplexer &
Demultiplexer::operator=(const Demultiplexer & src)
{
    Demultiplexer d(src);
    return d;
}

int
Demultiplexer::activate(void)
{}