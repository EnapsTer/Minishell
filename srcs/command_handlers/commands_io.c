/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:16:47 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 15:38:52 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "commands_utils.h"
#include "libft.h"
#include "print_errors.h"
#include "advanced_split_utils.h"
#include <string.h>
#include <errno.h>

int		handle_pipes(t_command **commands)
{
	int		i;
	int		pipes[2];

	i = 0;
	while (commands[i] && commands[i + 1])
	{
		if (pipe(pipes) == ERROR)
			return (ERROR);
		commands[i]->out = pipes[1];
		commands[i + 1]->in = pipes[0];
		i++;
	}
	return (TRUE);
}

int		handle_redirects(t_command *command)
{
	int		file_index;
	int		i;
	char	shield_char;

	file_index = 0;
	i = -1;
	shield_char = 0;
	while (command->files && command->str[++i])
	{
		change_shield_char(&shield_char, command->str, i, 0);
		if (!shield_char && !ft_strncmp(">>", &(command->str[i]), 2) && i++)
			command->out = get_dr(command->files[file_index++], command->out);
		else if (!shield_char && !ft_strncmp(">", &(command->str[i]), 1))
			command->out = get_rr(command->files[file_index++], command->out);
		else if (!shield_char && !ft_strncmp("<", &(command->str[i]), 1))
			command->in = get_lr(command->files[file_index++], command->in);
		if (command->in == ERROR || command->out == ERROR)
		{
			print_error(command->files[file_index - 1], strerror(errno));
			return (ERROR);
		}
	}
	return (TRUE);
}
