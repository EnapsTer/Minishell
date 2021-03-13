/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/13 16:41:51 by aherlind         ###   ########.fr       */
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
		if (!g_input_str)
			break;
		nullify_g_str();
	}
	return (ret);
}

int		main(int argc, char **argv, char **envp)
{
	// обработать $? и понять почему когда прога отрабатывает возвращаются разные код статусы
	// тесты на редиректы и пайпы
	// обработать open когда не открывается файл
	// спросить серегу про еще какие-то пункты
	// пример ls | exit 55 $? всегда у бинаркника
	// echo '\'"'
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

