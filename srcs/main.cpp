/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/11 19:27:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "InitiationDispatcher.hpp"
#include "ServerHandler.hpp"
#include "Server.hpp"

int	main(void)
{
	#ifdef DEBUG
		std::cout << "\033[1;31mDevelopment mode enable\033[0m" << std::endl;
	#endif
	std::cout << "\n-----TESTING-----\n\n";

	// std::cout << "\n---ONE SERVER---\n\n";
	// {
	// 	try
	// 	{
	// 		InitiationDispatcher idis; // Could create the demultiplexer and the handler table
	// 		HandlerTable ht;
	// 		Demultiplexer dmpx(ht); // Missing arguments, rework needed
	// 		idis.set_demultiplexer(dmpx);
	// 		idis.set_event_handler_table(ht);
	// 		const Server serv1(8080, inet_addr("127.0.0.1"));
	// 		ServerHandler sh(serv1, ht);
	// 		ht.add(serv1.getsockfd(), sh);
	// 		idis.handle_events();
	// 	}
	// 	catch(const std::exception &e)
	// 	{
	// 		std::cerr << e.what() << std::endl;
	// 	}
	// 	return 0;
	// }
	// std::cout << "\n---TWO SERVER---\n\n";
	// {
	// 	try
	// 	{
	// 		InitiationDispatcher idis; // Could create the demultiplexer and the handler table
	// 		HandlerTable ht;
	// 		Demultiplexer dmpx(ht); // Missing arguments, rework needed
	// 		idis.set_demultiplexer(dmpx);
	// 		idis.set_event_handler_table(ht);
	// 		const Server serv1(8080, inet_addr("127.0.0.1"));
	// 		const Server serv2(8081, inet_addr("127.0.0.1"));
	// 		ServerHandler sh1(serv1, ht);
	// 		ServerHandler sh2(serv2, ht);
	// 		ht.add(serv1.getsockfd(), sh1);
	// 		ht.add(serv2.getsockfd(), sh2);
	// 		idis.handle_events();
	// 	}
	// 	catch(const std::exception &e)
	// 	{
	// 		std::cerr << e.what() << std::endl;
	// 	}
	// 	return 0;
	// }

	std::cout << "\n---THREE SERVER---\n\n";
	{
		try
		{
			InitiationDispatcher idis; // Could create the demultiplexer and the handler table
			// HandlerTable ht;
			// Demultiplexer dmpx(ht); // Missing arguments, rework needed
			// idis.set_demultiplexer(dmpx);
			// idis.set_event_handler_table(ht);
			const Server serv1(8080, inet_addr("127.0.0.1"));
			const Server serv2(8081, inet_addr("127.0.0.1"));
			const Server serv3(8082, inet_addr("127.0.0.1"));
			idis.add_handle(serv1);
			idis.add_handle(serv2);
			idis.add_handle(serv3);
			idis.handle_events();
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		return 0;
	}

	// std::cout << "\n---TEN SERVER---\n\n";
}
