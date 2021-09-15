/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_check.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:12:54 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/15 17:44:34 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CHECK_H
# define LIBFT_CHECK_H

/*
**	Checking if string contain to_find character. Returns true at the
**	first occurence, false if none is found.
*/
bool			ft_is_char_in_str(const char to_find, const char *str);

/*
**	Checking in a string if all the characters are digits.
*/
bool			ft_is_only_digits(const char *str);

/*
** Checking if a character is numeric.
*/
bool			ft_is_digit(const char c);

/*
**	Cheking if 2 char * are entirely similar.
*/
bool			ft_strcmp(const char *src, const char *target);

/*
**	Checking if str string contains at least one character of the to_find
**	string. Return true at the first occurence, return false if none is found.
*/
bool			ft_is_charset_in_str(const char *str, const char *to_find);

/*
**	Cheking if a character is a white space.
*/
bool			ft_is_white_space(const char c);

/*
**	Checking if a character is an upper case alphabetic.
*/
bool			ft_is_upper(const char c);

/*
**	Checking if a character is a lower case alphabetic.
*/
bool			ft_is_lower(const char c);

/*
**	Checking if a character is alphabetic, upper or lower case.
*/
bool			ft_is_alpha(const char c);

/*
**	Checking if a character is rather numeric or alphabetic.
*/
bool			ft_is_alpha_num(const char c);

/*
**	Checking if the path of the file is valid by opening it and verifying
**	open() 's return.
*/
bool			ft_is_valid_file_path(const char *path);

#endif
