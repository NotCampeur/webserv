/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 11:22:56 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/24 20:10:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Checking if string contain to_find character. Returns true at the
**	first occurence, false if none is found.
*/

t_bool	ft_is_char_in_str(char to_find, char *str)
{
	int	index;

	index = 0;
	if (str == NULL)
	{
		return ((t_bool)ft_print_error(__PRETTY_FUNCTION__, __LINE__,
										FT_E_ARG));
	}
	while (str[index] != '\0')
	{
		if (str[index] == to_find)
			return (b_true);
		index++;
	}
	return (b_false);
}
