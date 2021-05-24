/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_upper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:25:38 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/24 20:11:32 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Checking if a character is an upper case alphabetic.
*/

t_bool	ft_is_upper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (b_true);
	return (b_false);
}
