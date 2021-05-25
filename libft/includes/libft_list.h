/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 08:21:26 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/25 18:18:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

/*
**	The t_list_node structure is designed to put any data in it as
**	a void pointer.
**	The second variable is a pointer to the next t_list_node,
**	in a chain of linked lists.
*/

typedef struct			s_list_node
{
	void				*data;
	struct s_list_node	*next;
}						t_list_node;

/*
**	Allocating memory for a t_list_node pointer and filling it with data.
**	Then returns the t_list_node pointer.
*/
t_list_node		*ft_malloc_node(void *data);

/*
**	Adding a node at the end of a linked list. See libft_list_node.h for further
**	informations on t_list_node structure.
*/
void			ft_list_add_back(t_list_node **list, t_list_node *node);

/*
**	Adding a node at the start of a linked list. See libft_list_node.h
**	for further informations on t_list_node structure.
*/
void			ft_list_add_front(t_list_node **list, t_list_node *node);

/*
**	Apply the destructor function to all the datas and free each nodes
*/
void			ft_list_clear(t_list_node **list, void (*destructor)(void*));

/*
**	Applying a function to all the list's datas.
*/
void			ft_list_iter(t_list_node *list, void (*function)(void*));

/*
**	Applying a function to all the nodes of a list and returning a new list
**	with the new datas. If the function fails, destroy the new list and returns
**	NULL.
*/
t_list_node		*ft_list_map(t_list_node *list, void *(*function)(void*),
												void (*destructor)(void*));

/*
**	Counting the number of nodes in a list and returning it.
*/
int				ft_list_size(t_list_node *list);

/*
**	Removing a node of a list (specified by node_index), and reforming the
**	list.
*/
void			ft_list_remove_node(t_list_node **list, size_t node_index,
												void (*destructor)(void*));

#endif
