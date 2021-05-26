/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_charset.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:59:06 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/26 14:31:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

/*
**	Counting the lenght of the string without the characters of
**	the charset and returning it.
*/

static int		len_without_charset(const char *str, const char *charset)
{
	int result;
	int index;

	result = 0;
	index = 0;
	if (str == NULL)
		return (result);
	while (str[index] != '\0')
	{
		if (ft_is_char_in_str(str[index], charset) == b_false)
			result++;
		index++;
	}
	return (result);
}

char			*ft_rm_charset(const char *str, const char *charset)
{
	char	*result;
	int		index;
	int		result_index;

	if (str == NULL || charset == NULL)
		return (NULL);
	index = 0;
	result_index = 0;
	result = ft_strnew(len_without_charset(str, charset));
	if (result == NULL)
		return (NULL);
	while (str[index] != '\0')
	{
		if (ft_is_char_in_str(str[index], charset) == b_false)
		{
			result[result_index] = str[index];
			result_index++;
		}
		index++;
	}
	return (result);
}
