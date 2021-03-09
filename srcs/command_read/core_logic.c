/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:12:41 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/09 15:46:37 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include "start.h"
#include <unistd.h>
#include "minishell.h"
#include <signal.h>

int	handle_new_line(int *continue_flag, char buf[131072], int count)
{
	buf[count - 1] = '\0';
	*continue_flag = ALL_OK;
	if (!(g_input_str = superstrjoin(g_input_str, buf)))
	{
		*continue_flag = MALLOC_ERROR;
		return (0);
	}
	return (is_read_syntax_ok(continue_flag));
}

void	exit_shell_from_read(int *continue_flag)
{
	if (!(g_input_str = ft_strdup("exit")))
	{
		*continue_flag = MALLOC_ERROR;
		return ;
	}
	*continue_flag = RETURN_STR;
	write(1, "fds", 1);
	exit (127);
}

void	continue_read_after_eof(int *continue_flag, char buf[131072])
{
	if (*continue_flag == NEW_LINE)
	{
		print_reading_error("minishell: syntax error: unexpected end of file\n");
		*continue_flag = SYNTAX_ERROR;
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

void	handle_input(int count, char buf[131072], int *continue_flag)
	{
		int		strlen;

		strlen = ministrlen(g_input_str) + count;
		buf[count] = '\0';
		if (strlen == 0)
			exit_shell_from_read(continue_flag);
		else if (buf[count - 1] != '\n')
			continue_read_after_eof(continue_flag, buf);
		else if (buf[count - 1] == '\n')
			if (handle_new_line(continue_flag, buf, count))
				*continue_flag = RETURN_STR;
	}

int	read_commands(void)
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
			handle_input(count, buf, &continue_flag);
		else
		{
			if (errno != EBADF)
				write(1, "count < 0", 9);
		}
	}
	return(continue_flag);
}
