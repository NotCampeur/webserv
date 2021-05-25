/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:31:41 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/25 18:09:43 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_print_error(const char *function_name, int line, const char *reason)
{
	ft_putstr(FT_RED"Exiting ");
	ft_putstr(FT_BOLD_RED);
	ft_putstr((char*)function_name);
	ft_putstr(FT_RED" at line ");
	ft_putstr(FT_BOLD_RED);
	ft_putnbr(line);
	if (reason != NULL)
	{
		ft_putstr(FT_RED" due to ");
		ft_putstr(FT_BOLD_RED);
		ft_putstr(reason);
	}
	ft_putstr("."FT_BASIC"\n");
	return (NULL);
}
