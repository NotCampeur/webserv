/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_map.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:17:49 by tguilbar          #+#    #+#             */
/*   Updated: 2021/05/25 18:18:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_node	*ft_list_map(t_list_node *list, void *(*function)(void *),
void (*destructor)(void *))
{
	t_list_node	*result;
	t_list_node	*new_node;

	if (list == NULL)
		return (NULL);
	result = ft_malloc_node((*function)(list->data));
	if (result == NULL)
		return (NULL);
	list = list->next;
	while (list != NULL)
	{
		new_node = ft_malloc_node((*function)(list->data));
		if (new_node == NULL)
		{
			ft_list_clear(&result, destructor);
			return (NULL);
		}
		ft_list_add_back(&result, new_node);
		list = list->next;
	}
	return (result);
}
