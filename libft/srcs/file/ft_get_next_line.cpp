/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:59:27 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/15 17:44:41 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

/*
**	Creating a line from storage.
*/

static char	*create_line(char *storage)
{
	int		index;
	char	*result;

	index = 0;
	while (storage[index] != '\0' && storage[index] != '\n')
		index++;
	result = ft_strsub(storage, 0, index);
	return (result);
}

/*
**	Removing a line from storage, so it remains only the surplus.
*/

static void	remove_line(char **storage)
{
	int		index;
	char	*tmp;
	int		new_len;

	index = 0;
	tmp = *storage;
	while (tmp[index] != '\0' && tmp[index] != '\n')
		index++;
	new_len = ft_strlen(tmp) - index - 1;
	if (new_len <= 0)
		*storage = NULL;
	else
		*storage = ft_strsub(tmp, index + 1, new_len);
	free(tmp);
}

/*
**	Will add what have been read at the end of the storage
**	until a new line or the end of file.
*/

static int	read_until_nl_or_eof(char **storage, char *buffer,
									int *read_return, int fd)
{
	while (ft_is_charset_in_str(*storage, "\n") == false
		&& *read_return != IS_END_OF_FILE)
	{
		*read_return = read(fd, buffer, BUFFER_SIZE);
		if (*read_return == IS_AN_ERROR)
			return (IS_AN_ERROR);
		ft_str_add_suffix(storage, buffer);
	}
	free(buffer);
	return (0);
}

int			ft_get_next_line(int fd, char **line)
{
	static char	*storage = NULL;
	char		*buffer;
	int			read_return;

	read_return = 1;
	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0)
		return (- 1);
	buffer = ft_strnew(BUFFER_SIZE);
	if (buffer == NULL)
		return (- 1);
	if (read_until_nl_or_eof(&storage, buffer, &read_return, fd) == -1)
		return (IS_AN_ERROR);
	*line = create_line(storage);
	remove_line(&storage);
	if (read_return == IS_END_OF_FILE)
		return (IS_END_OF_FILE);
	return (IS_A_LINE);
}
