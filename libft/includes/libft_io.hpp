/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:15:30 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/25 18:43:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

/*
**	Printing a character.
*/
void			ft_putchar(const char c);

/*
**	Printing a character in a file.
*/
void			ft_putchar(int fd, const char c);

/*
**	Printing a character in a file. The actual file is defined with
**	a path rathe than a file descriptor. Note that user can choose
**	3 modes to open the file (OVERWRITE, APPEND, CREATE). User also can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_putchar(const char *path, const char c, const char *mode);


/*
**	Printing a char * in standard output fd.
*/
void			ft_putstr(const char *str);

/*
**	Printing a char * in a file.
*/
void			ft_putstr(int fd, const char *str);

/*
**	Printing a string in a file. The actual file
**	is defined with a path rather than a file descriptor.
*/
void			ft_putstr(const char *path, const char *str, const char *mode);


/*
**	Printing an integer value.
*/
void			ft_putnbr(int nb);

/*
**	Printing an integer value in a file.
*/
void			ft_putnbr(int fd, int nb);

/*
**	Printing an integer value in a file. The actual file
**	is defined with a path rather than a file descriptor.
*/
void			ft_putnbr(const char *path, int nb, const char *mode);


/*
**	Printing a 2 dimensions characters array. Note that user can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_str_tab(const char *name, const char **tab);

/*
**	Printing a 2 dimensions characters array in a file. Note that user can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_str_tab(int fd, const char *name, const char **tab);

/*
**	Printing a 2 dimensions characters array in a file. The actual file is
**	defined with a path rathe than a file descriptor. Note that user can
**	choose 3 modes to open the file (OVERWRITE, APPEND, CREATE). User also can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_str_tab(const char *path,
				const char *name, const char **tab, const char *mode);


/*
**	Printing a 2 dimensions integers array. Note that user can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_int_tab(const char *name, int *tab, size_t len);

/*
**	Printing a 2 dimensions integers array in a file. Note that user can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_int_tab(int fd,
				const char *name, int *tab, size_t len);

#endif
