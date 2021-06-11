/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab_fp.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:49:30 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/26 14:31:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

/*
**	The 3 static functions bellow open the file with specific mode.
*/

static int	file_overwrite(const char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_TRUNC);
	return (fd);
}

static int	file_append(const char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_APPEND);
	return (fd);
}

static int	file_create(const char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 00700);
	return (fd);
}

void		ft_print_str_tab(const char *path,
			const char *name, const char **tab, const char *mode)
{
	int	fd;

	fd = -1;
	if (path == NULL || mode == NULL)
		return ;
	if (ft_strcmp(mode, "OVERWRITE") == b_true)
		fd = file_overwrite(path);
	else if (ft_strcmp(mode, "APPEND") == b_true)
		fd = file_append(path);
	else if (ft_strcmp(mode, "CREATE") == b_true)
		fd = file_create(path);
	else
		return ;
	if (fd == -1)
		return ;
	ft_print_str_tab(fd, name, tab);
	close(fd);
}