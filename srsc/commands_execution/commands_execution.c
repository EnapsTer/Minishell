/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:58:40 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/03 18:19:39 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advanced_split.h"
#include "delimiter_comparators.h"
#include "strs_utils.h"
#include "commands_parser.h"
#include "minishell.h"
#include "stdlib.h"

#include <stdio.h>
// echo 123 < text.txt
int			handle_redirects(char *str, t_command *command)
{
	while (*str)
	{

		str++;
	}
}

int 		init_command(t_command *command)
{
	command->name = NULL;
	command->args = NULL;
	command->files = NULL;
	command->in = 0;
	command->out = 1;
}

int			execute_command(char *str)
{
	t_command command;

	init_command(&command);
	if (parse_command(str, &command) == ERROR)
		return (ERROR);

	printf("command name = %s\n", command.name);
	while (command.args && *command.args)
		printf("args = %s\n", *command.args++);
	while (command.files && *command.files)
		printf("files = %s\n", *command.files++);
	printf("\n");

}

int			execute_commands(char *str)
{
	char	**semicoloned_strs;
	char	**piped_strs;
	int		i;
	int 	j;

	semicoloned_strs = advanced_split(str, is_semicolon, 0);
	i = -1;
	while (semicoloned_strs[++i])
	{
		piped_strs = advanced_split(semicoloned_strs[i], is_pipe, 0);
		j = -1;
		while (piped_strs[++j])
		{
			execute_command(piped_strs[j]);
		}
		free_str_arr(&piped_strs);
	}
	free_str_arr(&semicoloned_strs);
	return (TRUE);
}