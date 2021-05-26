/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count_c.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 10:55:11 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

int	ft_str_count_c(const char *str, const char c)
{
	int	result;
	int	index;

	result = 0;
	index = 0;
	if (str == NULL)
		return (0);
	while (str[index] != '\0')
	{
		if (str[index] == c)
			result++;
		index++;
	}
	return (result);
}
