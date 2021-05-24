/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add_prefixe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:02:39 by ncoudsi           #+#    #+#             */
/*   Updated: 2020/10/23 15:07:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Adding a prefixe to a string. Free the old string, re-allocate the new one.
*/

void		ft_str_add_prefixe(char *prefixe, char **str)
{
	char	*tmp;

	if (prefixe == NULL)
		return ((void)ft_print_error(__PRETTY_FUNCTION__, __LINE__, FT_E_ARG));
	tmp = ft_strdup(*str);
	free(*str);
	*str = ft_strjoin(prefixe, tmp);
	free(tmp);
}
