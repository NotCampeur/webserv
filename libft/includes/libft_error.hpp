/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 15:03:18 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/25 17:56:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ERROR_H
# define LIBFT_ERROR_H

/*
**	THIS WHOLE SECTION IS HEAVILY DEPRECATED!!!
**	As a cpp user you might want use exceptions.
*/

/*
**	Thoses defines will format the color output of write.
**	To use them do an ft_putstr(FT_COLOR).
*/

# define FT_RED "\033[0;31m"
# define FT_BOLD_RED "\033[1;31m"
# define FT_GREEN "\033[0;32m"
# define FT_BOLD_GREEN "\033[1;32m"
# define FT_YELLOW "\033[0;33m"
# define FT_BOLD_YELLOW "\033[1;33m"
# define FT_BLUE "\033[0;34m"
# define FT_BOLD_BLUE "\033[1;34m"
# define FT_MAGENTA "\033[0;35m"
# define FT_BOLD_MAGENTA "\033[1;35m"
# define FT_CYAN "\033[0;36m"
# define FT_BOLD_CYAN "\033[1;36m"
# define FT_BASIC "\033[0m"

/*
**	Thoses defines are intended to be sent in ft_print_error()
*/

# define FT_E_ARG "bad argument(s)"
# define FT_E_OPN "malfunction of open"
# define FT_E_RD "malfunction of read"
# define FT_E_MLC "malfunction of malloc"

/*
**	Will print a colored message according where the function have been called
**	and why, glad to the __PRETTY_NAME__ and __LINE__ attributes.
**	The return of this function is always NULL which grant you the possibility
**	to return the function directly in most of the case instead of
**	print the error and then return.
*/
void	*ft_print_error(const char *function_name, int line,
						const char *reason);

#endif
