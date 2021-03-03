/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:11:17 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/01 18:34:22 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start.h"
#include <unistd.h>
#include <signal.h>
#include "minishell.h"

void	signal_handle_read(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT, "\b\b  \b\b\nminishell$ ", 18);
		close(0);
		//g_input_fd = -1;
		//g_input_lenght = 0;
		if (g_input_str)
		{
		g_input_str[0] = '\0';
		g_input_str = NULL;
		}
	}
	if (signum == SIGQUIT)
		write(STDOUT, "\b\b  \b\b", 6);
}
