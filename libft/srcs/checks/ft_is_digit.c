/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 10:28:38 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/24 20:11:08 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checking if a character is numeric.
*/

t_bool	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (b_true);
	return (b_false);
}
