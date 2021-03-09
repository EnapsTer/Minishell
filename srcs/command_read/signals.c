/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:11:17 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/06 16:17:18 by nscarab          ###   ########.fr       */
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
		nullify_g_str();
	}
	if (signum == SIGQUIT)
		write(STDOUT, "\b\b  \b\b", 6);
}
