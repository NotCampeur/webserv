/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_convert.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:13:45 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/25 17:37:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONVERT_H
# define LIBFT_CONVERT_H

/*
**	Converting an integer value into a string filled with numerical characters
**	refering to the value, in a set base.
*/
char			*ft_itoa_base(long long int nbr, const char *base);

/*
**	Converting an integer value into a string filled with numerical characters
**	refering to the value.
*/
char			*ft_itoa(long long int nbr);

/*
**	Converting an integer value into a string filled with numerical characters
**	refering to the value, in an hexadecimal base.
*/
char			*ft_itoa_hexa(long long int nbr);

/*
**	Converting an integer value into a string filled with numerical characters
**	refering to the value, in an octadecimal base.
*/
char			*ft_itoa_octa(long long int nbr);

/*
**	Converting numericals characters in a string into an integer. Skip all the
**	spaces at the start of the string and accept one sign ('+' or '-'), then
**	take only numericals characters. As soon as we encounter a non numerical
**	character, we retrun the actual value of result.
*/
int				ft_atoi(const char *str);

#endif
