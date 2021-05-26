/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:11:40 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/25 18:44:45 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_H
# define LIBFT_MATH_H

/*
**	Counting the number of digits present in a number.
*/
size_t			ft_nbr_len(int nbr);

/*
**	Rounding up a floating point value.
*/
float			ft_roof(float value);

/*
**	Casting a floating point value into an integer to round it down, then
**	returning the rounded floating point value.
*/
float			ft_floor(float value);

/*
**	Returning a rounded value of a floating point.
*/
float			ft_round(float value);

/*
**	Returning an absolute value of an integer.
*/
int				ft_abs(int value);

/*
**	Returning the absolute value of a floating point.
*/
float			ft_abs(float value);

/*
**	This functions will use the XOR bit operator
**	to swap two integers values.
*/
void			ft_swap(int *x, int *y);

/*
**	This functions will use the XOR bit operator
**	to swap two char values.
*/
void			ft_swap(char *x, char *y);

#endif
