/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:04:01 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/24 17:23:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>

class Request
{
	private:
		std::string			_method;
		std::string			_path;
		std::string			_query;
		std::string			_HTTP_version;
		const std::string	_raw;
		
					Request();
					Request(const Request &to_copy);
	public:
					Request(const std::string &request);
					~Request();

		Request		&operator=(const Request &to_assign);
};

#endif