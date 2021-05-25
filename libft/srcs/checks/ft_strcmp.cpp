/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:55:32 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 18:01:50 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_strcmp(const char *src, const char *target)
{
	size_t	index;

	index = 0;
	if (src == NULL || target == NULL)
		return (b_false);
	while (src[index] != '\0' || target[index] != '\0')
	{
		if (src[index] != target[index])
			return (b_false);
		index++;
	}
	return (b_true);
}
