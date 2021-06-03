/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:04:01 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/03 18:27:27 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include "libft.hpp"

class request
{
	private:
		std::string			_method;
		std::string			_path;
		std::string			_query;
		std::string			_HTTP_version;
		const std::string	_raw;
		
					request();
					request(const request &to_copy);
	public:
					request(const std::string &request);
					~request();

		request		&operator=(const request &to_assign);
};

#endif