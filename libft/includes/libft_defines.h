/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:50:02 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 18:09:11 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DEFINES_H
# define LIBFT_DEFINES_H

/*
**	This enum is designed to replace booleans since this library is used in 42
**	school and the norme of the school does not authorize the use of external
**	libraries.
*/

/*
**	Obviously deprecated in Cpp because true and false are port of the basic keywords.
*/

typedef enum	e_bool
{
	b_true = 1,
	b_false = 0
}				t_bool;
#endif
