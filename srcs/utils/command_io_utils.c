/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_io_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:31:27 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 19:11:40 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

int		close_fd(int fd)
{
	if (fd != 0 && fd != 1)
		if (close(fd) < 0)
			return (ERROR);
	return (TRUE);
}

int		init_stdfd(t_fd *stdfd)
{
	if ((stdfd->in = dup(STDIN)) == ERROR)
		return (ERROR);
	if ((stdfd->out = dup(STDOUT)) == ERROR)
		return (ERROR);
	return (TRUE);
}

int		get_dr(char *file_name, int current_fd)
{
	int		fd;

	if (close_fd(current_fd) == ERROR)
		return (ERROR);
	fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY,
					S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	return (fd);
}

int		get_rr(char *file_name, int current_fd)
{
	int		fd;

	if (close_fd(current_fd) == ERROR)
		return (ERROR);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY,
						S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	return (fd);
}

int		get_lr(char *file_name, int current_fd)
{
	int		fd;

	if (close_fd(current_fd) == ERROR)
		return (ERROR);
	fd = open(file_name, O_RDONLY);
	return (fd);
}
