/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_lower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:27:37 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/24 20:11:16 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Checking if a character is a lower case alphabetic.
*/

t_bool	ft_is_lower(char c)
{
	if (c >= 'a' && c <= 'z')
		return (b_true);
	return (b_false);
}
