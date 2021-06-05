/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:15:41 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/05 11:33:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "request.hpp"

# define MAX_PENDING_CONNECTION 1
# define PORT 8080

class request;

class server
{
	private:
		int							_socket;
		struct sockaddr_in			_address;
		std::vector<int>			_client_socket;
		std::vector<request>		_client_request;
		bool						_is_verbose;

	public:
							server(const bool &verbose_state = false);
							server(const server &to_copy);
							~server();

		void				set_verbose(const bool &state);
		void				connection_handler();

	private:
		void				create_socket();
		void				init_addr_in();
		void				naming_serv_socket();
		void				set_listener();
		void				get_client_request();
		void				send_header(size_t content_length);
		void				send_response(const std::string &msg);
		void				accept_connection();

	public:
		server				&operator=(const server &to_assign);
	
		class UnableToCreateServerSocket : public std::exception
		{
			public:
				UnableToCreateServerSocket() throw() {}
				~UnableToCreateServerSocket() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to create a socket for the server : ")
					+ std::string(strerror(errno)))).c_str();}
		};

		class UnableToNameSocket : public std::exception
		{
			public:
				UnableToNameSocket() throw() {}
				~UnableToNameSocket() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to name the socket of the server : ")
					+ std::string(strerror(errno)))).c_str();}
		};

		class UnableToSetListener : public std::exception
		{
			public:
				UnableToSetListener() throw() {}
				~UnableToSetListener() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to set socket as listener : ")
					+ std::string(strerror(errno)))).c_str();}
		};

		class UnableToAcceptConnection : public std::exception
		{
			public:
				UnableToAcceptConnection() throw() {}
				~UnableToAcceptConnection() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to accept a connection : ")
					+ std::string(strerror(errno)))).c_str();}
		};

		class UnableToGetClientRequest : public std::exception
		{
			public:
				UnableToGetClientRequest() throw() {}
				~UnableToGetClientRequest() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to get client request : ")
					+ std::string(strerror(errno)))).c_str();}
		};

		class UnableToWriteToClient : public std::exception
		{
			public:
				UnableToWriteToClient() throw() {}
				~UnableToWriteToClient() throw() {}
				const char *what() const throw()
				{return (std::string(std::string("Unable to respond to the client : ")
					+ std::string(strerror(errno)))).c_str();}
		};
};

#endif
