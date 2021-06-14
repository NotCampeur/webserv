# include "webserv.hpp"
# include "InitiationDispatcher.hpp"

extern bool g_run_status;

void
sigint_handler(int sig_val)
{
    (void) sig_val;
    g_run_status = false;
	#ifdef DEBUG
		std::cout << "Sigint signal received" << '\n';
	#endif
}