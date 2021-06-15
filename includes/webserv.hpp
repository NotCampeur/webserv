/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez_home <ldutriez@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:29:35 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/15 10:44:56 by ldutriez_ho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <exception>
# include <string>
# include <cstring>
# include <ctime>

# include <algorithm>
# include <vector>
# include <map>

# include <errno.h>

# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <poll.h>
# include <signal.h>

# include "libft.hpp"
# include "webserv_param.hpp"
# include "Logger.hpp"
void    sigint_handler(int val);

#endif
