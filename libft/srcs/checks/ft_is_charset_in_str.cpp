/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_charset_in_str.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:14:11 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 18:49:43 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool			ft_is_charset_in_str(const char *str, const char *to_find)
{
	size_t	index;

	index = 0;
	if (str == NULL || to_find == '\0')
		return (b_false);
	while (str[index] != '\0')
	{
		if (ft_is_char_in_str(str[index], to_find) == b_true)
			return (b_true);
		index++;
	}
	return (b_false);
}
