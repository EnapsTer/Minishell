/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:20:36 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 15:58:27 by aherlind         ###   ########.fr       */
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
#include "libft.h"
#include <string.h>
#include <errno.h>
#include "print_errors.h"
#include "start.h"

t_command	*get_parsed_command(char *str, t_env *env)
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
	return (command);
}

t_command	**get_commands_by_pipes(char *str, t_env *env)
{
	t_command	**commands;
	char		**piped_strs;
	int			i;

	if (!(piped_strs = advanced_split(str, is_pipe, 0)))
		return (NULL);
	if (!(commands = malloc(sizeof(t_command *) *
			(str_arr_len(piped_strs) + 1))))
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

t_command	**get_commands(char *str, t_env **env)
{
	t_command	**commands;
	int			i;

	if ((commands = get_commands_by_pipes(str, *env)) == NULL)
	{
		print_error(0, strerror(errno));
		return (NULL);
	}
	if (handle_pipes(commands) == ERROR)
	{
		free_commands(&commands);
		print_error(0, strerror(errno));
		return (NULL);
	}
	i = -1;
	while (commands[++i] && commands[i]->args)
	{
		if (handle_redirects(commands[i]) == ERROR)
		{
			free_commands(&commands);
			return (NULL);
		}
	}
	return (commands);
}

int			change_exit_code(int ret, t_env **env)
{
	char	*exit_code;

	if (ret != -1)
	{
		if (!(exit_code = ft_itoa(ret)))
			return (ERROR);
		change_var_value("?", &exit_code, env);
	}
	return (TRUE);
}

int			handle_commands(char *str, t_env **env)
{
	char		**semicoloned_strs;
	t_command	**commands;
	int			ret;
	int			i;

	semicoloned_strs = advanced_split(str, is_semicolon, 0);
	i = -1;
	ret = -1;
	while (semicoloned_strs[++i])
	{
		if ((commands = get_commands(semicoloned_strs[i], env)) == NULL)
			ret = 1;
		else
		{
			ret = execute_commands(commands, env);
			free_commands(&commands);
		}
		if (!g_input_str)
			break ;
	}
	free_str_arr(&semicoloned_strs);
	if (change_exit_code(ret, env) == ERROR)
		return (ERROR);
	change_exit_code(ret, env);
	return (ret);
}
