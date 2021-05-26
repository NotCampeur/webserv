/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add_prefixe.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:02:39 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void		ft_str_add_prefixe(const char *prefixe, char **str)
{
	char	*tmp;

	if (prefixe == NULL)
		return ;
	tmp = ft_strdup(*str);
	free(*str);
	*str = ft_strjoin(prefixe, tmp);
	free(tmp);
}
