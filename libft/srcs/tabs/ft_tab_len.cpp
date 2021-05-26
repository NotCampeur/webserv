/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_len.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:13:14 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

/*
**	Calculating the number of entries in a 2 dimensions array.
*/

size_t	ft_tab_len(void **tab)
{
	size_t	result;

	result = 0;
	if (tab == NULL)
		return (0);
	while (tab[result] != NULL)
		result++;
	return (result);
}
