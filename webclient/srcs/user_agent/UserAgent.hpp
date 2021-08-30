/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserAgent.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:48:33 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/08/24 18:14:13 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_WEBCLIENT_CLIENT_HPP
# define WEBSERV_WEBCLIENT_CLIENT_HPP

# include "webclient.hpp"
namespace webclient
{
	class UserAgent
	{
		private:
			int					_target_port;
			int					_sockfd;
			struct sockaddr_in  _address;

		public:
			// With port 0, the OS assigns the port
			UserAgent(int port, int domain = AF_INET, int sock_protocol = SOCK_STREAM);
			UserAgent(UserAgent const & src);

			// Need to unlink socket here
			~UserAgent(void);
			
			void				send_request(std::string file_path);
			void				receive_response();

			int	getsockfd() const;
			UserAgent &  operator=(UserAgent const & src);

		private:
			UserAgent(void);

			void				create_socket(int domain, int type, int protocol = 0);
			void				init_addr_inputs(int domain, int port);
			void				connect_to_serv();

		// Class Exceptions:

		public:
			class UnableToCreateClientSocket : public std::exception
			{
					std::string	_msg;
				public:
					UnableToCreateClientSocket() throw();
					~UnableToCreateClientSocket() throw();
					const char *what() const throw();
			};

			class UnableToConnect : public std::exception
			{
					std::string	_msg;
				public:
					UnableToConnect() throw();
					~UnableToConnect() throw();
					const char *what() const throw();
			};
	};
}

#endif
