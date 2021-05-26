/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_node.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 09:46:35 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

t_list_node	*ft_malloc_node(void *data)
{
	t_list_node	*result;

	result = (t_list_node *)malloc(sizeof(t_list_node));
	if (result == NULL)
		return (NULL);
	result->data = data;
	result->next = NULL;
	return (result);
}
