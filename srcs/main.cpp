/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/10 10:18:24 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "Classes/Reactor/InitiationDispatcher.hpp"
#include "Classes/Reactor/ServerHandler.hpp"
#include "Classes/Server/Server.hpp"

int	main(void)
{
	#ifdef DEBUG
		std::cout << "\033[1;31mDevelopment mode enable\033[0m" << std::endl;
	#endif
	try
	{
		Server	server;

	std::cout << "\n-----TESTING-----\n\n";
/*
	std::cout << "\n---ONE SERVER---\n\n";
	{
		try
		{
			InitiationDispatcher idis; // Could create the demultiplexer and the handler table
			HandlerTable ht;
			Demultiplexer dmpx; // Missing arguments, rework needed
			const Server serv1(8080, inet_addr("127.0.0.1"));
			ServerHandler sh(serv1, ht);

		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		return 0;
	}
	std::cout << "\n---TWO SERVER---\n\n";


	std::cout << "\n---THREE SERVER---\n\n";

	std::cout << "\n---TEN SERVER---\n\n";
	*/
}
