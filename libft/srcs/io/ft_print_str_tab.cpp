/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:11:20 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/26 14:31:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

/*
**	Computing the offset to avoid a shift in output
*/

static void	print_offset(size_t nbr)
{
	size_t	i;

	i = 0;
	while (i < nbr)
	{
		ft_putchar(' ');
		i++;
	}
}

void		ft_print_str_tab(const char *name, const char **tab)
{
	size_t		index;
	size_t		line_offset;

	index = 0;
	if (tab == NULL)
		return ;
	line_offset = ft_nbr_len(ft_tab_len((void**)tab));
	if (name != NULL)
	{
		ft_putchar('{');
		ft_putstr(name);
		ft_putstr("}\n");
	}
	ft_putstr("-----===-----\n");
	while (tab != NULL && tab[index] != NULL)
	{
		ft_putnbr(index);
		print_offset(line_offset - ft_nbr_len(index));
		ft_putstr("--->");
		ft_putstr(tab[index]);
		ft_putstr("\n");
		index++;
	}
	ft_putstr("-----===-----\n");
}
