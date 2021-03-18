/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 20:19:15 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_handlers.h"
#include <unistd.h>
#include <libft.h>
#include <signal.h>
#include "start.h"

char	*g_input_str;

void	signal_handle_routine(int signum)
{
	if (signum == SIGQUIT)
		write(STDOUT, "Quit: 3", 7);
	write(STDOUT, "\n", 1);
}

int		routine(t_env **env)
{
	int		ret;

	while (1)
	{
		if (read_commands(env) == MALLOC_ERROR)
		{
			ft_putendl_fd("minishell: Cannot allocate memory", 2);
			nullify_g_str();
			break ;
		}
		signal(SIGINT, signal_handle_routine);
		signal(SIGQUIT, signal_handle_routine);
		if (!g_input_str)
			g_input_str = ft_strdup("");
		ret = handle_commands(g_input_str, env);
		if (!g_input_str)
			break ;
		nullify_g_str();
	}
	return (ret);
}

int		main(int argc, char **argv, char **envp)
{
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
