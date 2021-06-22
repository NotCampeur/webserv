/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez_home <ldutriez@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:33:01 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/06/22 12:49:55 by ldutriez_ho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webclient.hpp"
#include "Client.hpp"

void	client_manager(int port)
{
	for (int i(0); i < 2000; i++)
	{
		Client	client(port, AF_INET, SOCK_STREAM);
		client.send_request("HONK");
		client.receive_response();
	}
}

int main(int ac, char *av[])
{
	if (ac != 2)
		return EXIT_FAILURE;
	client_manager(atoi(av[1]));
	// int sock = 0;
	// long valread;
	// struct sockaddr_in serv_addr;
	// std::string hello("Hello from client");
	// char buffer[1024] = {0};

	// if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	// {
	// 	printf("\n Socket creation error \n");
	// 	return -1;
	// }
		
	// memset(&serv_addr, '0', sizeof(serv_addr));
		
	// serv_addr.sin_family = AF_INET;
	// serv_addr.sin_port = htons(PORT);
		
	// // Convert IPv4 and IPv6 addresses from text to binary form
	// if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	// {
	// 	printf("\nInvalid address/ Address not supported \n");
	// 	return -1;
	// }
		
	// if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	// {
	// 	printf("\nConnection Failed \n");
	// 	return -1;
	// }
	// send(sock , hello.c_str() , hello.size() , 0 );
	// printf("Hello message sent\n");
	// valread = read( sock , buffer, 1024);
	// printf("%s\n",buffer );
	Logger::quit();
	return 0;
}
