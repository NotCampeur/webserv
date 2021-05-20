/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:29:35 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/20 18:45:33 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_H
# define WEBSERV_H

# include <iostream>
# include <exception>
# include <string>
# include <algorithm>
# include <cstring>
# include <ctime>

# include <errno.h>

# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <netinet/in.h>

# define MAX_PENDING_CONNECTION 10
# define PORT 8080

#endif
