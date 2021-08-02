/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:29:35 by ldutriez          #+#    #+#             */
/*   Updated: 2021/08/02 18:58:55 by notcampeur       ###   ########.fr       */
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
# include <cctype>
# include <ctime>
# include <climits>
# include <sys/time.h>

# include <algorithm>
# include <vector>
# include <map>
# include <stack>
# include <utility>

# include <errno.h>

# include <sys/types.h>
# include <sys/stat.h>
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
