/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/13 15:49:22 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "InitiationDispatcher.hpp"
#include "ServerHandler.hpp"
#include "Server.hpp"
#include "json.hpp"
#include "Config.hpp"
#include "SystemException.hpp"
#include "ServerConfig.hpp"
#include "Environment.hpp"
#include "pthread.h"
int
serv_test(char * config_path)
{
	signal(SIGINT, sigint_handler);
	try
	{
		JsonFileReader	json_reader(config_path);
		try
		{
			InitiationDispatcher & idis = InitiationDispatcher::get_instance();
			try
			{
				Config		config(json_reader.objectify());
				
				config.print_to_log();
				config.apply();
			}
			catch(const std::exception& e)
			{
				Logger(LOG_FILE, error_type, error_lvl) << e.what();
				return EXIT_FAILURE;
			}
			idis.handle_events();
		}
		catch (const std::exception& e)
		{
			Logger(LOG_FILE, error_type, error_lvl) << e.what();
			return EXIT_FAILURE;
		}
	}
	catch (const std::exception& e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void *funct(void * var)
{
	std::cout << "Thread created" << std::endl;
	return var;
}

int	main(int ac, char *av[], char *envp[])
{
	int	return_status(EXIT_SUCCESS);
	if (ac > 2)
	{
		std::cerr << "Usage: ./webserv [config_path]" << std::endl;
		return EXIT_FAILURE;
	}
	Logger::accept_importance(all_lvl);
	Logger(LOG_FILE, basic_type, all_lvl) << "================[Webserv is starting]================";

	Environment::set_program_env(envp);
	// Environment::print_env();

	// Environment e1;
	// e1.add_cgi_env_var("HIHI", "hihi");
	// e1.add_cgi_env_var("HOHO", "hoho");
	// char **env = e1.get_cgi_env();
	// for (size_t i = 0; env[i]; i++)
	// 	std::cout << env[i] << '\n';

	pthread_t		thread;

	pthread_create(&thread, NULL, &funct, NULL);

	// serv_test(std::atol(av[1]));
	return_status = serv_test(av[1]);

	Logger::quit();
	return return_status;
}
