/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:29:35 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/30 17:04:20 by jmaydew          ###   ########.fr       */
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
# include <climits>
# include <sys/time.h>

# include <algorithm>
# include <vector>
# include <map>
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
