/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/19 14:22:13 by aherlind         ###   ########.fr       */
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

#include <stdio.h>
#include <fcntl.h>

int 	run_script(char **argv, t_env **env)
{
	char	*line;
	int 	fd;
	int		ret;

	line = NULL;
	ret = 1;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		g_input_str = ft_strdup(line);
		free(line);
		line = NULL;
		ret = handle_commands(g_input_str, env);

		if (!g_input_str)
			break ;
		nullify_g_str();
	}
	if (line)
	{
		g_input_str = ft_strdup(line);
		free(line);
		line = NULL;
		ret = handle_commands(g_input_str, env);
		nullify_g_str();
	}
	return (ret);
}

int		main(int argc, char **argv, char **envp)
{
	// echo "asdasd" > file.txt -- fixed
	// export HOME= ; cd
	// echo -n -nnn hello -n ; echo a
	// export  $var=test avec var unset
	// export la même variable - unicode
	// .
	// echo\ a - все что связано с \ без ковычек
	// > test - создается файл - fixed
	// export test="file1 file22" ;>$test
	// echo bonjour > > out_log
	// unset PATH ; ls --- error message

	t_env	*env;
	int		ret;

	if (!(env = get_env(envp)))
	{
		ft_putendl_fd("minishell: Cannot allocate memory", 2);
		return (1);
	}

	if (argc > 1)
	{
		ret = run_script(argv, &env);
		free_env(&env);
	}
	else
	{
		ret = routine(&env);
		free_env(&env);
	}
	return (ret);
}
