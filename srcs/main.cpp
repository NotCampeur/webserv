/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez_home <ldutriez@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/15 12:59:31 by ldutriez_ho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "InitiationDispatcher.hpp"
#include "ServerHandler.hpp"
#include "Server.hpp"

void	serv_test(long server_amount)
{
	try
	{
		signal(SIGINT, sigint_handler);
		InitiationDispatcher idis; // Could create the demultiplexer and the handler table
		for (long i(0); i < server_amount; i++)
		{
			const Server *serv = new Server(8080 + i, inet_addr("127.0.0.1"));
			idis.add_handle(*serv);
		}
		idis.handle_events();
	}
	catch(const std::exception &e)
	{
		Logger(LOG_FILE, error) << e.what();
	}
}

int	main(int ac, char *av[])
{
	if (ac <= 1)
		return EXIT_FAILURE;
	Logger() << "Launching the servers";
	
	serv_test(std::atol(av[1]));

	Logger::quit();
	return EXIT_SUCCESS;
}
