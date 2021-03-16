/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:37:51 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/12 22:15:39 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start.h"
#include <libft.h>
#include <stdlib.h>

void	ft_swap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
	return ;
}

int		is_mirrored_in_double_quotes(char c)
{
	if (c == '$' || c == '`' || c == '"' || c == '\\')
		return (1);
	return (0);
}

void	putstr_export_fd(char *str, int fd)
{
	ft_putstr_fd("\"", 1);
	while (*str)
	{
		if (is_mirrored_in_double_quotes(*str))
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(*str, fd);
		str++;
	}
	ft_putstr_fd("\"", 1);
}

int		is_env_declared(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(name, (tmp)->name))
			return (1);
		tmp = (tmp)->next;
	}
	return (0);
}
