/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:23:28 by aherlind          #+#    #+#             */
/*   Updated: 2020/11/10 16:23:31 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	check_buff(char **buffer, char **s, int chars_read)
{
	if (!chars_read)
		*buffer = NULL;
	if (s)
		free(*s);
}

int		read_chars_from_fd(int fd, char *s)
{
	int chars_read;

	chars_read = read(fd, s, BUFFER_SIZE);
	if (chars_read < 0)
	{
		free(s);
		return (-1);
	}
	s[chars_read] = '\0';
	return (chars_read);
}

int		add_buf_to_line(char **buffer, char **line)
{
	int		char_index;
	char	*tmp;

	if (*buffer)
	{
		if ((char_index = index_of_char(*buffer, '\n')) != -1)
		{
			(*buffer)[char_index] = '\0';
			if (!(*line = ft_gnl_strdup(*buffer)))
				return (-2);
			tmp = *buffer;
			if (!(*buffer = ft_gnl_strdup(*buffer + char_index + 1)))
				return (-2);
			free(tmp);
			return (char_index);
		}
		else
		{
			if (!(*line = ft_gnl_strdup(*buffer)))
				return (-2);
			free(*buffer);
		}
	}
	return (-1);
}

int		search_end_of_line(char **s, int *char_index, char **buffer)
{
	if ((*char_index = index_of_char(*s, '\n')) >= 0)
	{
		(*s)[*char_index] = '\0';
		if (!(*buffer = ft_gnl_strdup(*s + *char_index + 1)))
			return (-1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*buffers;
	char		*s;
	int			chars_read;
	int			char_index;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	chars_read = 1;
	*line = NULL;
	char_index = -1;
	s = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if ((char_index = add_buf_to_line(&buffers, line)) == -2)
		return (-1);
	while (char_index == -1 && chars_read > 0)
	{
		if ((chars_read = read_chars_from_fd(fd, s)) == -1
				|| search_end_of_line(&s, &char_index, &(buffers))
				|| !(*line = ft_gnl_strjoin(*line, s)))
			return (-1);
	}
	check_buff(&(buffers), &s, chars_read);
	return (chars_read ? 1 : 0);
}
