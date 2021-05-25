/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:14:19 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 17:03:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copy the entries of a 2 dimensions array in another one.
*/

void	ft_tab_cpy(void **dst, void **src)
{
	int	index;

	index = 0;
	if (dst == NULL || src == NULL)
		return ;
	while (src[index] != NULL)
	{
		dst[index] = src[index];
		index++;
	}
}
