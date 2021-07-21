/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/16 14:04:51 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "InitiationDispatcher.hpp"
#include "ServerHandler.hpp"
#include "Server.hpp"
#include "SYSException.hpp"

void	serv_test(long server_amount)
{
	signal(SIGINT, sigint_handler);
	InitiationDispatcher & idis = InitiationDispatcher::get_instance();

	try
	{
		for (long i(0); i < server_amount; i++)
		{
			const Server *serv = new Server(8080 + i, inet_addr("127.0.0.1"));
			idis.add_server_handle(*serv);
		}
		idis.handle_events();

	}
	catch (const SYSException & e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
		return ;
	}
	catch(const std::exception& e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
		return ;
	}
}

int	main(int ac, char *av[])
{
	if (ac <= 1)
		return EXIT_FAILURE;

	Logger::accept_importance(all_lvl);
	Logger(LOG_FILE, basic_type, all_lvl) << "Launching the servers " << 42 << " yeah baby";

	serv_test(std::atol(av[1]));

	Logger::quit();
	return EXIT_SUCCESS;
}
