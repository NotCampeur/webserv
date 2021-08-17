#include "Environment.hpp"
#include <iostream>
#include <cstring>

Environment::Environment(void) :
_cgi_env(NULL)
{}

// Environment::Environment(Environment const & src)
// {
//     (void)src;
// }

Environment::~Environment(void) {}

// Environment &
// Environment::operator=(Environment const & src)
// {
// 	(void)src;
//     return (*this);
// }

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

void
Environment::add_cgi_env_var(const std::string & name, const std::string & val)
{
	std::pair<std::string, std::string> p(name, val);
	_cgi_env_var.push_back(p);
}

char **
Environment::get_cgi_env(void)
{
	size_t i = 0;
	if (_program_env)
	{
		while (_program_env[i])
		{
			i++;
		}
	}

	if (_cgi_env != NULL)
	{
		delete_cgi_env();
	}

	size_t env_size = i + _cgi_env_var.size();
	_cgi_env = new char * [env_size + 1];
	for (size_t j = 0 ; j < env_size + 1 ; j++)
		_cgi_env[j] = NULL;

	set_cgi_env();
	return _cgi_env;
}

void
Environment::set_cgi_env(void)
{
	size_t i = 0;
	if (_program_env)
	{
		for (; _program_env[i]; i++)
		{
			char *entry = new char [std::strlen(_program_env[i]) + 1];
			std::strcpy(entry, _program_env[i]);
			_cgi_env[i] = entry;
		}
	}
	for (size_t j = 0; j < _cgi_env_var.size(); j++)
	{
		size_t name_len = _cgi_env_var[j].first.size();
		size_t value_len = _cgi_env_var[j].second.size();
		char * entry = new char [name_len + value_len + 2]; // +2 for '=' and \0
		std::strcpy(entry, _cgi_env_var[j].first.c_str());
		entry[name_len] = '=';
		std::strcpy(entry + name_len + 1, _cgi_env_var[j].second.c_str());
		_cgi_env[i + j] = entry;
	}
}

void
Environment::delete_cgi_env(void)
{
	for (size_t i = 0; _cgi_env[i]; i++)
	{
		delete [] _cgi_env[i];
	}
	delete [] _cgi_env;
	_cgi_env = NULL;
}
