# include "webserv.hpp"
# include "InitiationDispatcher.hpp"

extern bool g_run_status;

void
sigint_handler(int sig_val)
{
    (void) sig_val;
    g_run_status = false;
	Logger(LOG_FILE, error_type, error_lvl) << "Sigint signal received";
}
