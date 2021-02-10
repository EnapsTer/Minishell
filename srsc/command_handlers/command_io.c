/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:16:47 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/09 15:01:23 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "commands_utils.h"
#include "libft.h"

int 		handle_pipes(t_command **commands)
{
	int		i;
	int 	pipes[2];

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

int			handle_redirects(t_command *command)
{
	int		file_index;
	int 	i;

	file_index = 0;
	i = 0;
	while (command->str[i])
	{
		if (!ft_strncmp(">>", &(command->str[i]), 2))
			command->out = get_double_redirect_fd(command->files[file_index++],
										 command->out);
		else if (!ft_strncmp(">", &(command->str[i]), 1))
			command->out = get_right_redirect_fd(command->files[file_index++],
										command->out);
		else if (!ft_strncmp("<", &(command->str[i]), 1))
			command->in = get_left_redirect_fd(command->files[file_index++],
												 command->out);
	//обработка errno
		i++;
	}
	return (TRUE);
}