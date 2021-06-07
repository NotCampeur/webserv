/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:28:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/07 14:32:04 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(void)
{
	#ifdef DEBUG
		std::cout << "Development mode enable" << std::endl;
	#endif
	try
	{
		server	server;

		server.connection_handler();
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
