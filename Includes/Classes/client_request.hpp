/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_request.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:04:01 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/07 14:12:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_REQUEST_HPP
# define CLIENT_REQUEST_HPP

# include "webserv.hpp"

class client_request
{
	private:
		std::string					_method;
		std::string					_path;
		std::string					_query;
		std::string					_HTTP_version;
		std::vector<std::string>	_headers;
		std::vector<std::string>	_body;
		
									client_request();
			void					set_method(std::string &client_request);
			void					set_path(std::string &client_request);
			void					set_query(std::string &client_request);
			void					set_HTTP_version(std::string &client_request);
			void					set_headers(std::string &client_request);
			void					set_body(std::string &client_request);
	public:
									client_request(const char *client_request);
									client_request(std::string &client_request);
									client_request(const client_request &to_copy);
									~client_request();

		client_request				&operator=(const client_request &to_assign);
};

#endif