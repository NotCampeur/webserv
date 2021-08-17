#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

#include <string>
#include <vector>
#include <utility>

class Environment
{
	private:
		static char ** _program_env;
	
	public:
		static void	set_program_env(char **envp);
		static void print_env(void); // DEBUG
	
		typedef	std::vector<std::pair<std::string, std::string> > env_vec;
	private:
		char	**_cgi_env;
		env_vec	_cgi_env_var;

	public:

    	Environment(void);
    	~Environment(void);
		

		char **		get_cgi_env(void);
		void		add_cgi_env_var(const std::string & name, const std::string & val);

	private:
    	Environment(Environment const & src);
		Environment &  operator=(Environment const & src);

		void	set_cgi_env(void);
		void	delete_cgi_env(void);
		// void	copy_program_env(char *env[]);
		// void	copy_cgi_env_var(char *env[]);
};

#endif
