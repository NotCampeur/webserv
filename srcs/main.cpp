/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/08/25 19:13:41 by notcampeur       ###   ########.fr       */
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

void
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
				config.apply(idis);
			}
			catch(const std::exception& e)
			{
				Logger(LOG_FILE, error_type, error_lvl) << e.what();
			}
			idis.handle_events();
		}
		catch (const std::exception& e)
		{
			Logger(LOG_FILE, error_type, error_lvl) << e.what();
			return ;
		}
	}
	catch (const std::exception& e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
		return ;
	}
}

int
main(int ac, char *av[])
{
	(void)ac;
	Logger::accept_importance(all_lvl);
	Logger(LOG_FILE, basic_type, all_lvl) << "Launching the servers " << 42 << " yeah baby";

	serv_test(av[1]);

	Logger::quit();
	return EXIT_SUCCESS;
}