/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_digits.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:44:35 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

t_bool	ft_is_only_digits(const char *str)
{
	size_t index;

	index = 0;
	if (str == NULL)
		return (b_false);
	while (str[index] != '\0')
	{
		if (ft_is_digit(str[index]) == b_false)
			return (b_false);
		index++;
	}
	return (b_true);
}
