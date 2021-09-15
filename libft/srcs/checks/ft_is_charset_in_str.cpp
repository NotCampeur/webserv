/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_charset_in_str.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:14:11 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/09/15 17:44:56 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

bool			ft_is_charset_in_str(const char *str, const char *to_find)
{
	size_t	index;

	index = 0;
	if (str == NULL || to_find == '\0')
		return (false);
	while (str[index] != '\0')
	{
		if (ft_is_char_in_str(str[index], to_find) == true)
			return (true);
		index++;
	}
	return (false);
}
