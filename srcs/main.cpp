/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/29 12:36:56 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "InitiationDispatcher.hpp"
#include "ServerHandler.hpp"
#include "Server.hpp"
#include "json.hpp"
#include "Config.hpp"

JsonFileReader
read_config(char * path)
{
	if (path != NULL)
	{
		JsonFileReader result(path);
		return result;
	}
	JsonFileReader result;
	return result;
}

int
main(int ac, char *av[])
{
	if (ac > 2)
		return EXIT_FAILURE;

	signal(SIGINT, sigint_handler);
	Logger::accept_importance(all_lvl);
	Logger(LOG_FILE, basic_type, all_lvl) << "Launching the servers " << 42 << " yeah baby";
	try
	{
		JsonFileReader	json_reader(read_config(av[1]));
		Config			config(json_reader.objectify());
		config.print_to_log();
		try
		{
			InitiationDispatcher idis;
			try
			{
				config.apply(idis);
			}
			catch(const std::exception& e)
			{
				Logger(LOG_FILE, error_type, error_lvl) << e.what();
			}
			idis.handle_events();
		}
		catch(const std::exception &e)
		{
			Logger(LOG_FILE, error_type, error_lvl) << e.what();
		}
	}
	catch(const std::exception & e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
	}
	Logger::quit();
	return EXIT_SUCCESS;
}