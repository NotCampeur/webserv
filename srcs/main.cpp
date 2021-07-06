/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/06 22:18:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "InitiationDispatcher.hpp"
#include "ServerHandler.hpp"
#include "Server.hpp"
#include "json.hpp"

void
serv_test(long server_amount)
{
	try
	{
		signal(SIGINT, sigint_handler);
		InitiationDispatcher idis; // Could create the demultiplexer and the handler table
		try
		{
			for (long i(0); i < server_amount; i++)
			{
				const Server *serv = new Server(8080 + i, inet_addr("127.0.0.1"));
				idis.add_handle(*serv);
			}
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
	if (ac <= 1)
		return EXIT_FAILURE;

	Logger::accept_importance(all_lvl);
	Logger(LOG_FILE, basic_type, all_lvl) << "Launching the servers " << 42 << " yeah baby";
	try
	{
		JsonFileReader	json_reader(read_config(av[2]));
		JsonObject		obj(json_reader.objectify());

		obj.print(1);
		std::cout << std::endl;
		serv_test(std::atol(av[1]));
	}
	catch(const std::exception& e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
	}
	Logger::quit();
	return EXIT_SUCCESS;
}
