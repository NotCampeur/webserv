/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char_in_str.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 11:22:56 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/09/15 17:44:56 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

bool	ft_is_char_in_str(char to_find, const char *str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return (false);
	while (str[index] != '\0')
	{
		if (str[index] == to_find)
			return (true);
		index++;
	}
	return (false);
}
