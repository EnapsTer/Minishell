/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:46:54 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/11 17:24:30 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "start.h"
#include <stdlib.h>
#include "minishell.h"
#include <libft.h>

void	nullify_g_str(void)
{
	char	*tmp;

	if (g_input_str)
	{
		tmp = g_input_str;
		strzero(g_input_str);
		g_input_str = NULL;
		free(tmp);
	}
}

void	print_syntax_error(char *str, t_env **env, int *continue_flag)
{
	char *buf;

	*continue_flag = SYNTAX_ERROR;
	if (!(buf = ft_strdup("258")))
	{
		*continue_flag = MALLOC_ERROR;
		return ;
	}
	change_var_value("?", &buf, env);
	ft_putstr_fd("minishell: syntax error near unexpected ", 2);
	ft_putendl_fd(str, 2);
	write(2, "minishell$ ", 11);
	nullify_g_str();
}

void	nullify_str(char **buf)
{
	char	*tmp_c;

	if (buf && *buf)
	{
		tmp_c = *buf;
		strzero(*buf);
		*buf = NULL;
		free(tmp_c);
	}
}
