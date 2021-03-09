/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/09 15:46:37 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advanced_split.h"
#include "minishell.h"
#include "command_handlers.h"
#include "delimiter_comparators.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
///////////=============================================================////////////////
#include <libft.h>
#include <stdio.h>
#include <signal.h>
#include "start.h"
#include "strs_utils.h"

// выводить errno
// exit code $?
// предварительный парсинг на ошибки ; ' "
// капс команды
// cat | ls
// тест на закрытие in fd пример
// echo "\$" ------ echo '\$'
//

int		g_int_fd;
char	*g_input_str;


void	signal_handle_routine(int signum)
{
	if (signum == SIGQUIT)
		write(STDOUT, "Quit: 3", 7);
	write(STDOUT, "\n", 1);
}

void	routine (t_env **env)
{
	while (1)
	{
		if (read_commands() == MALLOC_ERROR)
		{
			ft_putendl_fd("minishell: Cannot allocate memory", 2);
			nullify_g_str();
			break;
		}
		signal(SIGINT, signal_handle_routine);
		signal(SIGQUIT, signal_handle_routine);
		if (!g_input_str)
			g_input_str = ft_strdup("");
		//printf("|%s|\n", g_input_str);
		handle_commands(g_input_str, env);
		nullify_g_str();
	}
}

int	main(int argc, char **argv, char **envp)
{
//	char **strs = advanced_split("echo '$PATH'", is_semicolon, 1);
//
//	while (*strs)
//	{
//		printf("%s\n", *strs);
//		strs++;
//	}
//	char **str = ft_split("", ';');
	t_env *env;

	if (!(env = get_env(envp)))
		{
			ft_putendl_fd("minishell: Cannot allocate memory", 2);
			return (1);
		}

	///////////////////print env////////////////////////////
	/*
	t_env *begin;
	begin = env;
	while (env->next)
	{
		printf("%s|||%s\n", env->name, env->value);
		env = env->next;
	}
	printf("%s|||%s\n", env->name, env->value);
	env = begin;
	*/
	///////////////////print env////////////////////////////
	routine(&env);
	free_env(&env);
	return (0);
}

