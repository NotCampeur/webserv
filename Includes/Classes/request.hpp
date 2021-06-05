/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:04:01 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/05 13:15:01 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "webserv.hpp"

class request
{
	private:
		std::string					_method;
		std::string					_path;
		std::string					_query;
		std::string					_HTTP_version;
		std::vector<std::string>	_headers;
		std::vector<std::string>	_body;
		
									request();
			void					set_method(std::string &request);
			void					set_path(std::string &request);
			void					set_query(std::string &request);
			void					set_HTTP_version(std::string &request);
			void					set_headers(std::string &request);
			void					set_body(std::string &request);
	public:
									request(const char *request);
									request(std::string &request);
									request(const request &to_copy);
									~request();

		request						&operator=(const request &to_assign);
};

#endif