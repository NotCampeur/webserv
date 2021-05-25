/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_file.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:07:15 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/25 17:46:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FILE_H
# define LIBFT_FILE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define IS_NOT_A_LINE 2
# define IS_A_LINE 1
# define IS_END_OF_FILE 0
# define IS_AN_ERROR -1

/*
**	Getting the next line of a file and store it in a string. We consider a line
**	as an undefined number of characters terminated with '\n'. The function
**	returns 1 if a line has been found, 0 if the enf of file has beem reached
**	and -1 if an error occured.
*/
int				ft_get_next_line(int fd, char **line);

/*
**	Opening a file and getting its datas line by line. Storing it in a char **
**	and returning it. If the path to the file is incorrect, returning NULL.
*/
char			**ft_get_file(const char *path);

/*
**	Opening a file and getting its datas line by line. Storing it in a char **
**	and returning it. If the fd is incorrect, returning NULL.
*/
char			**ft_get_file(int fd);

#endif
