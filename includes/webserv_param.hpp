#ifndef WEBSERV_PARAM_H
# define WEBSERV_PARAM_H

# define MAX_PENDING_CONNECTION 50
# define RECV_BUF_SIZE 1024
# define DEMULTIMPEXER_TIMEOUT 1 * 1000

# ifdef DEBUG
#  define DEBUG_STREAM std::cerr
# endif

#endif