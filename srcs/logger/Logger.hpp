#ifndef WEBSERV_LOGGER_HPP
# define WEBSERV_LOGGER_HPP

# include "webserv.hpp"
# include <semaphore.h>

// This enum store the flags about the type of entry.
// Some entry like the errors need further specifications.
// Which are given by this enum.
typedef enum log_type
{
	basic_type,
	error_type
}	log_type;

// This enum store the flags about the importance restriction,
typedef enum log_importance_level
{
	error_lvl = 0x001,
	major_lvl = 0x002,
	minor_lvl = 0x004,
	debug_lvl = 0x008,
	all_lvl   = error_lvl | major_lvl | minor_lvl | debug_lvl
}	log_importance_level;

// Will force the unary expression to return a log_importance_level and not a int.
log_importance_level operator|(const log_importance_level & value_a,
								const log_importance_level & value_b);

// Will force the unary expression to return a log_importance_level and not a int.
log_importance_level operator^(const log_importance_level & value_a,
								const log_importance_level & value_b);

// A class to simplify logs creation.
// The common usage is
// Logger() << "This is a nice log entry" << 42 << '42';
// You can set which messages will be printed glade to :
// Logger::accept_importance(error_lvl | major_lvl | debug_lvl);
// You must call Logger::quit() before the exit to avoid leaks.
class Logger
{
	public:
		typedef std::map<std::string, std::ofstream *>	map_type;

		Logger(std::string path = LOG_FILE, log_type type = basic_type, log_importance_level importance = major_lvl);
		~Logger();

		// This function will set the accepted level.
		// If you try to write an entry below the accepted level
		// nothing will happen.
		// If you never set it yourself every messages are accepted.
		static void	accept_importance(log_importance_level accepted_importance);

		// Incremente the _multi_process_lock to ensure a multi_process running.
		static void	process_forked(void);

		// This function need to be called right before the end of the program.
		// The ofstream map will be correctly deleted.
		static void	quit(void);

		// This tell you if the current instance will be allow to write entry.
		bool	is_important_enough(void) const;
		
		Logger	&operator<<(const std::string & entry);
		Logger	&operator<<(const char * const & entry);
		Logger	&operator<<(const char & entry);
		Logger	&operator<<(const int & entry);
		Logger	&operator<<(const ssize_t & entry);
		Logger	&operator<<(const size_t & entry);

	private:
		void	put_timestamp(void);

		static std::string			_path;
		static log_type				_type;
		static map_type				_files;
		static log_importance_level	_accepted_importance;
		static sem_t *				_multi_process_lock;
		log_importance_level		_importance;
};

#endif
