/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:10:21 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/15 17:53:38 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
# define LIBFT_STRING_H

# include <cstdlib>
# include <string>
# include <vector>

/*
**	Allocating memory for a new string of len lenght and filling it with '\0'.
*/
char			*ft_strnew(size_t len);

/*
**	Copying the characters of src string in a new string. Note that we allocate
**	memory for the new string before copying.
*/
char			*ft_strdup(const char *src);

/*
**	Allocating memory for a new string containing only c character.
**	Then returns the string.
*/
char			*ft_strdup_c(const char c);

/*
**	Counting the lenght of a pointer to char and returning it.
*/
size_t			ft_strlen(const char *str);

/*
** DEPRECATED FUNCTION :
** size_t			ft_strlen_arg(char *str, char c);
*/

/*
**	Copying the characters of src string in dest string. Returns dest after the
**	copy. Note that we do not proceed to any memory allocation.
*/
char			*ft_strcpy(const char *src, char *dest);

/*
**	Troncating a string from the start index of src until len characters
**	are copied. Returns a heap allocated string. Note that we do not free src.
*/
char			*ft_strsub(const char *src, size_t start, size_t len);

/*
**	Merging 2 strings in one. Then returns the new string. Note that we
**	allocate memory for the new string, but we do not free str1 and str2.
*/
char			*ft_strjoin(const char *str1, const char *str2);

/*
**	Searching for the full needle string is found in the haystack string.
**	If needle is found, returns a pointer on haystack string, starting at
**	the first character of needle. If needle is not found, returns NULL.
*/
char			*ft_strstr(const char *haystack, const char *needle);

/*
**	Splitting a string into multiple ones depending on sep character.
**	Returns a pointer to the first string of the multiple new ones.
*/
char			**ft_split(const char *src, const char sep);

/*
**	Splitting a string into a vector of string depending on sep string.
**	Returns a vecotr<string> containing every strings.
*/
std::vector<std::string>
ft_split(const std::string &src, const std::string &sep);

/*
**	Adding a prefixe to a string. FREE THE OLD STRING, re-allocate the new one.
*/
void			ft_str_add_prefixe(const char *prefixe, char **str);

/*
**	Adding a suffix to a string. FREE THE OLD STRING, re-allocate the new one.
*/
void			ft_str_add_suffix(char **str, const char *suffix);

/*
**	Counting the number of itterations of c character in str string.
*/
int				ft_str_count_c(char *str, char c);

/*
**	Searching for the full needle char * in the haystack char *, but
**	only checking len characters. If needle is found, returns a pointer on
**	haystack char * (not const), starting at the first character of needle.
**	If needle is not found, returns NULL.
*/
char			*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*
**	Removing all characters of a charset of a string and returning
**	the cleaned string.
*/
char			*ft_rm_charset(char *str, char *charset);

/*
**	Removing all characters of a charset of a referenced string.
*/
std::string
ft_rm_charset(std::string str, std::string charset);

#endif
