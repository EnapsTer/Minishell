/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/02 19:55:53 by nscarab          ###   ########.fr       */
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
	int		errors;

	while (1)
	{
		read_commands(&errors);
		signal(SIGINT, signal_handle_routine);
		signal(SIGQUIT, signal_handle_routine);
		//printf("%s\n", g_input_str);
		handle_commands(g_input_str, env);
		if (g_input_str)
		{
			g_input_str[0] = '\0';
			//free(str);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env *env;

	env = get_env(envp);
	///////////////////print env////////////////////////////
	//t_env *begin;
	//begin = env;
	//while (env->next)
	//{
		//printf("%s|||%s\n", env->name, env->value);
		//env = env->next;
	//}
	//printf("%s|||%s\n", env->name, env->value);
	//env = begin;
	///////////////////print env////////////////////////////
	routine(&env);
	//предварительный парсинг
	free_env(&env);
	return (0);
}

