/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_charset.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:59:06 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/15 17:55:26 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.hpp"
#include <algorithm>
#include "libft_check.hpp"
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
		if (ft_is_char_in_str(str[index], charset) == false)
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
		if (ft_is_char_in_str(str[index], charset) == false)
		{
			result[result_index] = str[index];
			result_index++;
		}
		index++;
	}
	return (result);
}

std::string
ft_rm_charset(std::string str, std::string charset)
{
	size_t	charset_len(0);

	if (str.empty() || charset.empty())
		return str;
	charset_len = charset.size();
	for (unsigned int i = 0; i < charset_len; ++i)
	{
		str.erase(remove(str.begin(), str.end(), charset[i]), str.end());
	}
	return str;
}