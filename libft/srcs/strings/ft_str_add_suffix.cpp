/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add_suffix.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:32:29 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	ft_str_add_suffix(char **str, const char *suffix)
{
	char	*tmp;

	if (suffix == NULL)
		return ;
	tmp = ft_strdup(*str);
	free(*str);
	*str = ft_strjoin(tmp, suffix);
	free(tmp);
}
