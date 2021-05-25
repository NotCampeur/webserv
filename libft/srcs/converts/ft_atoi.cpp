/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 10:47:17 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 17:40:04 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	index;
	int	sign;

	if (str == NULL)
		return (1);
	result = 0;
	index = 0;
	sign = 1;
	while (str[index] == ' ')
		index++;
	if (str[index] == '+')
		index++;
	else if (str[index] == '-')
	{
		index++;
		sign *= -1;
	}
	while (str[index] != '\0' && (str[index] >= '0' && str[index] <= '9'))
	{
		result = (result * 10) + (str[index] - '0');
		index++;
	}
	return (result * sign);
}
