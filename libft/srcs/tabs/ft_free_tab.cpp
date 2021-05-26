/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:13:46 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

/*
**	Free every entity in a 2 dimensions array and free the array itself.
*/

void	ft_free_tab(void **tab)
{
	int	index;

	index = 0;
	if (tab == NULL)
		return ;
	while (tab[index] != NULL)
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}
