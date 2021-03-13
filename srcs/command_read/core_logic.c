/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:12:41 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/13 11:18:11 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include "start.h"
#include <unistd.h>
#include "minishell.h"
#include <signal.h>

static int	handle_new_line(int *continue_flag, char buf[131072], int count, t_env **env)
{
	buf[count - 1] = '\0';
	*continue_flag = ALL_OK;
	if (!(g_input_str = superstrjoin(g_input_str, buf)))
	{
		*continue_flag = MALLOC_ERROR;
		return (0);
	}
	return (is_read_syntax_ok(continue_flag, env));
}

static void	exit_shell_from_read(int *continue_flag)
{
	nullify_g_str();
	if (!(g_input_str = ft_strdup("exit")))
	{
		*continue_flag = MALLOC_ERROR;
		return ;
	}
	*continue_flag = RETURN_STR;
}

static void	continue_read_after_eof(int *continue_flag, char buf[131072], t_env **env)
{
	if (*continue_flag == NEW_LINE)
	{
		*continue_flag = SYNTAX_ERROR;
		print_syntax_error("end of file", env, continue_flag);
		return;
	}
	write(STDOUT, "  \b\b", 4);
	if (!(g_input_str = superstrjoin(g_input_str, buf)))
	{
		*continue_flag = MALLOC_ERROR;
		return ;
	}
	return;
}

static void	handle_input(int count, char buf[131072], int *continue_flag, t_env **env)
	{
		int		strlen;

		strlen = ministrlen(g_input_str) + count;
		buf[count] = '\0';
		if (strlen == 0)
			exit_shell_from_read(continue_flag);
		else if (buf[count - 1] != '\n')
			continue_read_after_eof(continue_flag, buf, env);
		else if (buf[count - 1] == '\n')
			if (handle_new_line(continue_flag, buf, count, env))
				*continue_flag = RETURN_STR;
	}

int	read_commands(t_env **env)
{
	int		count;
	char	buf[131072];
	int		continue_flag;

	continue_flag = ALL_OK;
	g_input_str = NULL;
	write(STDOUT, "minishell$ ", 11);
	while (continue_flag == ALL_OK || continue_flag == SYNTAX_ERROR
			||continue_flag == NEW_LINE)
	{
		buf[0] = '\0';
		signal(SIGINT, signal_handle_read);
		signal(SIGQUIT, signal_handle_read);
		count = read (0, buf, 131071);
		if (count >= 0)
			handle_input(count, buf, &continue_flag, env);
		else
			exit_shell_from_read(&continue_flag);
	}
	return(continue_flag);
}
