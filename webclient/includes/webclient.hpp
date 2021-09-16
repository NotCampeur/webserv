/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webclient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:32:47 by ldutriez_ho       #+#    #+#             */
/*   Updated: 2021/09/16 23:11:07 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_WEBCLIENT_HPP
# define WEBSERV_WEBCLIENT_HPP

# include <stdio.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <unistd.h>
# include <netinet/in.h>
# include <string.h>
# include <arpa/inet.h>
# include <errno.h>

# include <iostream>
# include <fstream>
# include <sstream>
# include <exception>
# include <string>
# include <cstring>
# include <ctime>
# include <random>

# include <algorithm>
# include <vector>
# include <map>

# define CLIENT_LOG_FILE "webclient.log"
# define PORT 8080
# include "Logger.hpp"

#endif
