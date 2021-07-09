#ifndef WEBSERV_PARAM_H
# define WEBSERV_PARAM_H

# define MAX_PENDING_CONNECTION 50
# define RECV_BUF_SIZE 1024
# define DEMULTIMPEXER_TIMEOUT 10 * 1000

# ifdef DEBUG
#  define DEBUG_STREAM std::cerr
# endif
# define LOG_FILE "webserv.log"

# define MAX_URI_SIZE	8000 //Minimum request line size per rfc 7230 is 8000 octets

# define MAX_CLIENT_BODY_SIZE 1000000 //1MB

# define CLIENT_TIMEOUT 30 //In seconds

#endif
