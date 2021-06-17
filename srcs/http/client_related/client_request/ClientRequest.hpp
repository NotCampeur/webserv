/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:04:01 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/17 20:14:43 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CLIENT_REQUEST_HPP
# define WEBSERV_CLIENT_REQUEST_HPP

# include "webserv.hpp"

class ClientRequest
{
	private:
		std::string					_method;
		std::string					_path;
		std::string					_query;
		std::string					_HTTP_version;
		std::vector<std::string>	_headers;
		std::vector<std::string>	_body;
		
									ClientRequest();
			void					set_method(std::string &ClientRequest);
			void					set_path(std::string &ClientRequest);
			void					set_query(std::string &ClientRequest);

			//	The three following functions assign until a \n but don't add it in the string  
			//	Note that the \\r is kept.  
			void					set_HTTP_version(std::string &ClientRequest);
			void					set_headers(std::string &ClientRequest);
			void					set_body(std::string &ClientRequest);
	public:
									ClientRequest(const char *ClientRequest);
									ClientRequest(std::string &ClientRequest);
									ClientRequest(const ClientRequest &to_copy);
									~ClientRequest();

		ClientRequest				&operator=(const ClientRequest &to_assign);
};

#endif