#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

#include <string>
#include <map>

class Environment
{
	private:
		static char ** _program_env;
	
	public:
		static void	set_program_env(char **envp);
		static void print_env(void); // DEBUG

	private:
		std::map<std::string, std::string>	_cgi_env_var;

	public:

    	Environment(void);
    	Environment(Environment const & src);
    	~Environment(void);
		
		Environment &  operator=(Environment const & src);

		char **		get_cgi_env(void);
		void		add_cgi_env_var(const std::string & name, const std::string & val);
};

#endif
