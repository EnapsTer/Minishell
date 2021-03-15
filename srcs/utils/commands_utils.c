/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:14:59 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 15:27:13 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "strs_utils.h"
#include <stdlib.h>

int		init_command(t_command *command)
{
	command->args = NULL;
	command->files = NULL;
	command->str = NULL;
	command->in = 0;
	command->out = 1;
	return (TRUE);
}

void	free_command(t_command **command)
{
	t_command *temp_command;

	temp_command = *command;
	if (temp_command->args)
		free_str_arr(&temp_command->args);
	if (temp_command->files)
		free_str_arr(&temp_command->files);
	if (temp_command->str)
		free(temp_command->str);
	free(*command);
	*command = NULL;
}

void	free_commands(t_command ***commands)
{
	int		i;

	if (*commands == NULL)
		return ;
	i = 0;
	while ((*commands)[i])
	{
		free_command(&((*commands)[i]));
		i++;
	}
	free(*commands);
	*commands = NULL;
}

int		get_commands_len(t_command **commands)
{
	int	len;

	len = 0;
	while (commands[len])
		len++;
	return (len);
}
