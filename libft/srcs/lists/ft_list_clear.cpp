/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:47:03 by tguilbar          #+#    #+#             */
/*   Updated: 2021/05/26 14:31:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	ft_list_clear(t_list_node **list, void (*destructor)(void*))
{
	t_list_node *tmp;

	if (*list == NULL)
		return ;
	while (*list != NULL)
	{
		tmp = *list;
		if (destructor != NULL)
			(*destructor)(tmp->data);
		*list = tmp->next;
		free(tmp);
	}
}
