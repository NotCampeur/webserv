/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:32:44 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 18:34:47 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystack_index;
	size_t	needle_index;

	haystack_index = 0;
	if (haystack == NULL)
		return (NULL);
	if (needle == NULL || ft_strlen(needle) == 0)
		return ((char *)(haystack));
	while (haystack[haystack_index] != '\0' && haystack_index < len)
	{
		needle_index = 0;
		while (needle[needle_index] == haystack[haystack_index + needle_index]
		&& haystack_index + needle_index < len)
		{
			if (needle[needle_index + 1] == '\0')
				return ((char *)(haystack + haystack_index));
			needle_index++;
		}
		haystack_index++;
	}
	return (NULL);
}
