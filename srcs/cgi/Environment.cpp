#include "Environment.hpp"
#include <iostream>

Environment::Environment(void) {}

Environment::Environment(Environment const & src)
{
    (void)src;
}

Environment::~Environment(void) {}

Environment &
Environment::operator=(Environment const & src)
{
	(void)src;
    return (*this);
}

char **Environment::_program_env; //Necessary to use static member inside function members

void
Environment::print_env(void)
{
	char **env = _program_env;
	while (*env != NULL)
	{
		std::cout << *env << '\n';
		env++;
	}
}

void
Environment::set_program_env(char **envp)
{
	_program_env = envp;
}



char **
Environment::get_cgi_env(void)
{
	if (!_program_env)
		return NULL;

	int i = 0;
	
	while (_program_env[i])
	{
		i++;
	}

	char **env = new char * [i + _cgi_env_var.size()];

	int i = 0;
	while (_program_env[i])
	{
		env
		i++;
	}
	

	return ;
}

void
Environment::add_cgi_env_var(const std::string & name, const std::string & val)
{
	_cgi_env_var.insert(name, val);
}