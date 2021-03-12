/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:20:36 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/12 18:13:15 by aherlind         ###   ########.fr       */
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

t_command *get_parsed_command(char *str, t_env *env)
{
	t_command	*command;

	if (!(command = malloc(sizeof(t_command))))
		return (NULL);
	init_command(command);
	if (parse_command(str, command, env) == ERROR)
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

t_command **get_commands_by_pipes(char *str, t_env *env)
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
		commands[i] = get_parsed_command(piped_strs[i], env);
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
	int 		ret;
	int			i;
	int 		j;

	semicoloned_strs = advanced_split(str, is_semicolon, 0);
	i = -1;
	while (semicoloned_strs[++i] && ret != ERROR)
	{
		commands = get_commands_by_pipes(semicoloned_strs[i], *env);
		handle_pipes(commands);
		j = -1;
		while (commands[++j])
			handle_redirects(commands[j]);
		ret = execute_commands(commands, env);
		free_commands(&commands);
		if (!g_input_str)
			break;
	}
	free_str_arr(&semicoloned_strs);
	return (ret);
}
