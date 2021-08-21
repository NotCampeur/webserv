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
#include "SystemException.hpp"
#include "ServerConfig.hpp"
#include "Environment.hpp"

void	serv_test(long server_amount)
{
	signal(SIGINT, sigint_handler);
	InitiationDispatcher & idis = InitiationDispatcher::get_instance();

	try
	{
		for (long i(0); i < server_amount; i++)
		{
			std::string location = "localhost";
			std::string port = "8080";
			ServerConfig *config = new ServerConfig(location, port, true);
			std::string default_file_dir = "server_content/index.html";
			config->set_default_file_dir(default_file_dir);
			std::string error_404 = "server_content/error_404";
			config->add_error_page_path(404, error_404);
			config->add_cgi_path("py", "server_content/cgi-bin/bin.py");
			
			Server *serv = new Server(config, 8080 + i, inet_addr("127.0.0.1"));
			idis.add_server_handle(*serv);
		}
		idis.handle_events();
	}
	catch (const SystemException & e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
		return ;
	}
	catch (const std::exception& e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
		return ;
	}
}

int	main(int ac, char *av[], char *envp[])
{
	if (ac <= 1)
		return EXIT_FAILURE;

	Logger::accept_importance(all_lvl);
	Logger(LOG_FILE, basic_type, all_lvl) << "Launching the servers " << 42 << " yeah baby";

	Environment::set_program_env(envp);
	Environment::print_env();

	Environment e1;
	e1.add_cgi_env_var("HIHI", "hihi");
	e1.add_cgi_env_var("HOHO", "hoho");
	char **env = e1.get_cgi_env();
	for (size_t i = 0; env[i]; i++)
		std::cout << env[i] << '\n';

	serv_test(std::atol(av[1]));

	Logger::quit();
	return EXIT_SUCCESS;
}
