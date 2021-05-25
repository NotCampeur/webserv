/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:34:11 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/25 17:53:11 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_get_file(const char *path)
{
	char	**result;
	int		fd;
	char	*line;

	result = NULL;
	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 3)
		return (NULL);
	while (ft_get_next_line(fd, &line) > 0)
	{
		ft_add_to_tab((void *)line, (void ***)&result);
	}
	ft_add_to_tab((void *)line, (void ***)&result);
	close(fd);
	return (result);
}


char	**ft_get_file(int fd)
{
	char	**result;
	char	*line;

	result = NULL;
	line = NULL;
	if (fd < 3)
		return (NULL);
	while (ft_get_next_line(fd, &line) > 0)
	{
		ft_add_to_tab((void *)line, (void ***)&result);
	}
	ft_add_to_tab((void *)line, (void ***)&result);
	return (result);
}
