/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:20:36 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/25 18:59:03 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:58:40 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/10 10:52:56 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advanced_split.h"
#include "delimiter_comparators.h"
#include "strs_utils.h"
#include "command_handlers.h"
#include "commands_execution.h"
#include "commands_utils.h"
#include "commands_parser.h"
#include "minishell.h"
#include "stdlib.h"

#include <stdio.h>
#include "start.h"

t_command	*get_parsed_command(char *str)
{
	t_command	*command;

	if (!(command = malloc(sizeof(t_command))))
		return (NULL);
	init_command(command);
	if (parse_command(str, command) == ERROR)
	{
		free_command(&command);
		return (NULL);
	}
//	printf("command name = %s\n", command->name);
//	for (int i = 0; command->args && command->args[i]; i++)
//		printf("args = %s\n", command->args[i]);
//	for (int i = 0; command->files && command->files[i]; i++)
//		printf("args = %s\n", command->files[i]);
//	printf("\n");
	return (command);

}

t_command **get_commands_by_pipes(char *str)
{
	t_command	**commands;
	char		**piped_strs;
	int 		i;

	if (!(piped_strs = advanced_split(str, is_pipe, 0)))
		return (NULL);
	if (!(commands = malloc(sizeof(t_command *) * (str_arr_len(piped_strs) + 1))))
		return (NULL);
	i = 0;
	while (piped_strs[i])
	{
		commands[i] = get_parsed_command(piped_strs[i]);
		i++;
	}
	free_str_arr(&piped_strs);
	commands[i] = NULL;
	return (commands);
}


int handle_commands(char *str, t_env **env)
{
	char		**semicoloned_strs;
	t_command	**commands;
	int			i;
	int 		j;

	semicoloned_strs = advanced_split(str, is_semicolon, 0);
	i = -1;
	while (semicoloned_strs[++i])
	{
		// echo hello > file1 | ls ; echo | ls ../
		commands = get_commands_by_pipes(semicoloned_strs[i]);
		handle_pipes(commands);
		j = -1;
		while (commands[++j])
		{
			handle_redirects(commands[j]);
//			printf("str = |%s|\n", commands[j]->str);
//			printf("command name = %s\n", commands[j]->name);
//			for (int index = 0; commands[j]->args && commands[j]->args[index]; index++)
//				printf("args = %s\n", commands[j]->args[index]);
//			for (int index = 0; commands[j]->files && commands[j]->files[index]; index++)
//				printf("files = %s\n", commands[j]->files[index]);
//			printf("in = %d ---- out = %d\n", commands[j]->in, commands[j]->out);
//			printf("\n");
		}
		if (execute_commands(commands, env) == ERROR)
			return (ERROR);
		free_commands(&commands);
	}
	free_str_arr(&semicoloned_strs);
	return (TRUE);
}
