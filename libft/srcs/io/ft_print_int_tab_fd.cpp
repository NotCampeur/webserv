/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_tab_fd.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:52:13 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	ft_print_int_tab(int fd, const char *name, int *tab, size_t len)
{
	size_t		index;

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
	while (tab && index < len)
	{
		ft_putnbr(fd, index);
		ft_putstr(fd, "--->[");
		ft_putnbr(fd, tab[index]);
		ft_putstr(fd, "]\n");
		index++;
	}
	ft_putstr(fd, "-----===-----\n");
}
