/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:00:18 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 18:42:06 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int fd, int nbr)
{
	if (fd == -1)
		return ;
	if (nbr < 0)
	{
		ft_putchar(fd, '-');
		nbr = nbr * -1;
	}
	if (nbr >= 10)
		ft_putnbr(fd, nbr / 10);
	ft_putchar(fd, (nbr % 10) + '0');
}
