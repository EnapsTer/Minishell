/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/13 11:21:30 by aherlind         ###   ########.fr       */
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
#include <libft.h>
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

char	*g_input_str;

void	signal_handle_routine(int signum)
{
	if (signum == SIGQUIT)
		write(STDOUT, "Quit: 3", 7);
	write(STDOUT, "\n", 1);
}

int routine (t_env **env)
{
	int		ret;
	char 	*exit_code;

	while (1)
	{
		if (read_commands(env) == MALLOC_ERROR)
		{
			ft_putendl_fd("minishell: Cannot allocate memory", 2);
			nullify_g_str();
			break;
		}
		signal(SIGINT, signal_handle_routine);
		signal(SIGQUIT, signal_handle_routine);
		if (!g_input_str)
			g_input_str = ft_strdup("");
		ret = handle_commands(g_input_str, env);
		//обработать эти строки и перенести их
		if (ret != -1)
		{
			exit_code = ft_itoa(ret);
			change_var_value("?", &exit_code, env);
		}
		if (!g_input_str)
			break;
		nullify_g_str();
	}
	return (ret);
}

int		main(int argc, char **argv, char **envp)
{
	// обработать $? и понять почему когда прога отрабатывает возвращаются разные код статусы
	// почему то ошибка 127 когда просто нажимаю на контрол д обсудить с серегой
	// сделать норм билтины с пайпами
	// тесты на редиректы и пайпы
	// обработать open когда не открывается файл
	// спросить серегу про еще какие-то пункты
	t_env	*env;
	int		ret;

	if (!(env = get_env(envp)))
	{
		ft_putendl_fd("minishell: Cannot allocate memory", 2);
		return (1);
	}
	ret = routine(&env);
	free_env(&env);
	return (ret);
}

