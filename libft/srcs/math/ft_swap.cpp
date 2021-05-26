/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:18:37 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/26 14:31:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	ft_swap(int *x, int *y)
{
	if (x == NULL || y == NULL)
		return ;
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}

void	ft_swap(char *x, char *y)
{
	if (x == NULL || y == NULL)
		return ;
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}
