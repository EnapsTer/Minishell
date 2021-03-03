/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:12:41 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/02 15:37:57 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include "start.h"
#include <unistd.h>
#include "minishell.h"
#include <signal.h>

int	handle_new_line(int *continue_flag, char (*buf)[131072], int count)
{
	(*buf)[count - 1] = '\0';
	g_input_str = superstrjoin(g_input_str, *buf);
	return (is_read_syntax_ok(continue_flag));
}

void	read_init(void)
{
	g_input_str = NULL;
	g_int_fd = dup(0);
	write(STDOUT, "minishell$ ", 11);
}

void	exit_shell_from_read(void)
{
	//g_input_str = ft_strdup("exit");
	write(STDOUT, "exit\n", 5);
	//return (g_input_str);
	exit(127);
}

void	continue_read_after_eof(int *continue_flag, char buf[131072])
{
	if (*continue_flag == 2)
	{
		print_reading_error("minishell: syntax error: unexpected end of file\n");
		*continue_flag = 1;
		return;
	}
	write(STDOUT, "  \b\b", 4);
	g_input_str = superstrjoin(g_input_str, buf);
	return;
}

char	*read_commands(int *errors)
{
	int		count;
	int		strlen;
	char	buf[131072];
	int		continue_flag;

	strlen = 0;
	continue_flag = 0;
	read_init();
	while (1)
	{
		buf[0] = '\0';
		signal(SIGINT, signal_handle_read);
		signal(SIGQUIT, signal_handle_read);
		count = read (0, buf, 131071);
		if (count >= 0)
		{
			strlen = ministrlen(g_input_str) + count;
			buf[count] = '\0';
			if (strlen == 0)
				exit_shell_from_read();
			else if (buf[count - 1] != '\n')
				continue_read_after_eof(&continue_flag, buf);
			else if (buf[count - 1] == '\n')
				if (handle_new_line(&continue_flag, &buf, count))
					return(g_input_str);
		}
		else
		{
			if (errno != EBADF)
				write(1, "count < 0", 9);
		}
		dup2(g_int_fd, 0);
	}
}

