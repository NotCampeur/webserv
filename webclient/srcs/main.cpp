/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:33:01 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/06/22 20:42:13 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webclient.hpp"
#include "Client.hpp"

void	client_manager(int amount, std::string request_path, int range_start, int range_end)
{
	std::vector<webclient::Client> clients;
	(void)range_end;
	// for (int i(0); i < amount; i++)
	// {
	// 	// if (range_start == range_end)
	// 	// 	clients.push_back(webclient::Client(range_start, AF_INET, SOCK_STREAM));
	// 	// else
	// 	// 	clients.push_back(webclient::Client(rand() % (range_end - range_start) + range_start, AF_INET, SOCK_STREAM));
	// }
	for (int i(0); i < amount; i++)
	{
		clients.push_back(webclient::Client(range_start, AF_INET, SOCK_STREAM));
		clients[i].send_request(request_path);
		clients[i].receive_response();
	}
	// for (int i(0); i < amount; i++)
}

void	unit_test_one(int amount, std::string request_path, int range_start, int range_end)
{
	(void)range_end;
	for (int i(0); i < amount; i++)
	{
		if (range_start == range_end)
			webclient::Client cl(range_start, AF_INET, SOCK_STREAM);
		else
			webclient::Client cl(rand() % (range_end - range_start) + range_start, AF_INET, SOCK_STREAM);
		cl.send_request(request_path);
		cl.receive_response();
	}
}

int main(int ac, char *av[])
{
	if (ac != 5)
		return EXIT_FAILURE;
	srand(time(NULL));
	Logger::accept_importance(all_lvl);
	try
	{
		// client_manager(atoi(av[1]), av[2], atoi(av[3]), atoi(av[4]));
		unit_test_one(atoi(av[1]), av[2], atoi(av[3]), atoi(av[4]));
	}
	catch(const std::exception& e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
	}
	Logger::quit();
	return 0;
}
