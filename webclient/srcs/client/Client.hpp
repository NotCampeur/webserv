/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:48:33 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/06/22 17:06:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_WEBCLIENT_CLIENT_HPP
# define WEBSERV_WEBCLIENT_CLIENT_HPP

# include "webclient.hpp"
namespace webclient
{
	class Client
	{
			private:
			
			int					_target_port;
			int					_sockfd;
			struct sockaddr_in  _address;

		public:
			// With port 0, the OS assigns the port
			Client(int port, int domain = AF_INET, int sock_protocol = SOCK_STREAM);
			Client(Client const & src);

			// Need to unlink socket here
			~Client(void);
			
			void				send_request(std::string file_path);
			void				receive_response();

			int	getsockfd() const;
			Client &  operator=(Client const & src);

		private:
			Client(void);

			void				create_socket(int domain, int type, int protocol = 0);
			void				init_addr_inputs(int domain, int port);
			void				connect_to_serv();

		// Class Exceptions:

		public:
			class UnableToCreateClientSocket : public std::exception
			{
				const char *what() const throw();
			};

			class UnableToConnect : public std::exception
			{
					const char *what() const throw();
			};

	};
}

#endif
