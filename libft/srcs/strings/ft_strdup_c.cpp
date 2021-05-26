/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_c.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:57:19 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

char	*ft_strdup_c(const char c)
{
	char	*result;

	result = ft_strnew(1);
	if (result == NULL)
		return (NULL);
	result[0] = c;
	return (result);
}
