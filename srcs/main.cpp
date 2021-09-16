/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/16 23:35:48 by notcampeur       ###   ########.fr       */
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
#include "Arguments.hpp"

int
serv_test(void)
{
	signal(SIGINT, sigint_handler);
	try
	{
		JsonFileReader	json_reader(Arguments::get_instance().config_path());
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
				Logger(Arguments::get_instance().log_file(), error_type, error_lvl) << e.what();
				return EXIT_FAILURE;
			}
			idis.handle_events();
		}
		catch (const std::exception& e)
		{
			Logger(Arguments::get_instance().log_file(), error_type, error_lvl) << e.what();
			return EXIT_FAILURE;
		}
	}
	catch (const std::exception& e)
	{
		Logger(Arguments::get_instance().log_file(), error_type, error_lvl) << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	main(int ac, char *av[], char *envp[])
{
	int	return_status(EXIT_SUCCESS);

	if (Arguments::get_instance().apply(ac, av) == false)
	{
		std::cerr << "Type \"webserv --help\" to know the basic usage" << std::endl;
		return EXIT_FAILURE;
	}
	Logger(Arguments::get_instance().log_file(), basic_type, all_lvl) << "================[Webserv is starting]================";
	Logger(Arguments::get_instance().log_file(), basic_type, all_lvl) << "Process ID of the server : " << getpid();
	Environment::set_program_env(envp);
	// Environment::print_env();

	// Environment e1;
	// e1.add_cgi_env_var("HIHI", "hihi");
	// e1.add_cgi_env_var("HOHO", "hoho");
	// char **env = e1.get_cgi_env();
	// for (size_t i = 0; env[i]; i++)
	// 	std::cout << env[i] << '\n';

	// serv_test(std::atol(av[1]));
	return_status = serv_test();

	Logger::quit();
	return return_status;
}
