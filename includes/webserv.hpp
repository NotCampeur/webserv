/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:29:35 by ldutriez          #+#    #+#             */
/*   Updated: 2021/06/17 20:40:14 by ldutriez         ###   ########.fr       */
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
# include <sys/time.h>

# include <algorithm>
# include <vector>
# include <map>
# include <utility>

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
# include "webserv_sig_handler.hpp"

#endif
