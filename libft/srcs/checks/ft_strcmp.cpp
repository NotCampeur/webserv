/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:55:32 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/09/15 17:44:56 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

bool	ft_strcmp(const char *src, const char *target)
{
	size_t	index;

	index = 0;
	if (src == NULL || target == NULL)
		return (false);
	while (src[index] != '\0' || target[index] != '\0')
	{
		if (src[index] != target[index])
			return (false);
		index++;
	}
	return (true);
}
