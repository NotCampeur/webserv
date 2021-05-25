/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab_fd.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:01:04 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 18:43:02 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_str_tab(int fd, const char *name, const char **tab)
{
	size_t	index;

	index = 0;
	if (fd == -1 && tab == NULL)
		return ;
	if (name != NULL)
	{
		ft_putchar(fd, '{');
		ft_putstr(fd, name);
		ft_putstr(fd, "}\n");
	}
	ft_putstr(fd, "-----===-----\n");
	while (tab != NULL && tab[index] != NULL)
	{
		ft_putnbr(fd, index);
		ft_putstr(fd, "--->[");
		ft_putstr(fd, tab[index]);
		ft_putstr(fd, "]\n");
		index++;
	}
	ft_putstr(fd, "-----===-----\n");
}
