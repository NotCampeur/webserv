/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_white_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:14:14 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/24 20:11:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Cheking if a character is a white space.
*/

t_bool	ft_is_white_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\n' || c == '\r' ||
	c == '\f' || c == ' ')
		return (b_true);
	return (b_false);
}
