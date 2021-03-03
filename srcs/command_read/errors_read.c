/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:46:54 by nscarab           #+#    #+#             */
/*   Updated: 2021/02/28 17:10:01 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "start.h"
#include <stdlib.h>
#include "minishell.h"

void	print_reading_error(char *str)
{
	char	*tmp;

		write(STDOUT, str, ministrlen(str));
		write(STDOUT, "minishell$ ", 11);
		if (g_input_str)
		{
		tmp = g_input_str;
		strzero(g_input_str);
		g_input_str = NULL;
		free (g_input_str);
		}
}

