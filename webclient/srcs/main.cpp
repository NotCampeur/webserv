/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:33:01 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/06/24 14:52:50 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webclient.hpp"
#include "Client.hpp"

void	simultaneous_test(int amount, std::string request_path, int range_start, int range_end)
{
	int									port(0);
	std::random_device					rd;
	std::mt19937						rng(rd());
	std::uniform_int_distribution<int>	uni(range_start, range_end);
	std::vector<webclient::Client> clients;

	for (int i(0); i < amount; i++)
	{
		port = uni(rng);
		clients.push_back(webclient::Client(port, AF_INET, SOCK_STREAM));
	}
	for (int i(0); i < amount; i++)
		clients[i].send_request(request_path);
	for (int i(0); i < amount; i++)
		clients[i].receive_response();
}

void	unit_test(int amount, std::string request_path, int range_start, int range_end)
{
	int									port(0);
	std::random_device					rd;
	std::mt19937						rng(rd());
	std::uniform_int_distribution<int>	uni(range_start, range_end);

	for (int i(0); i < amount; i++)
	{
		port = uni(rng);
		webclient::Client cl(port, AF_INET, SOCK_STREAM);
		cl.send_request(request_path);
		cl.receive_response();
	}
}

int main(int ac, char *av[])
{
	if (ac != 5)
		return EXIT_FAILURE;
	Logger::accept_importance(all_lvl);
	try
	{
		// simultaneous_test(atoi(av[1]), av[2], atoi(av[3]), atoi(av[4]));
		unit_test(atoi(av[1]), av[2], atoi(av[3]), atoi(av[4]));
	}
	catch(const std::exception& e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
	}
	Logger::quit();
	return 0;
}
