/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:37:51 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/09 19:33:58 by nscarab          ###   ########.fr       */
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

void	ft_sort_array(char **tab)
{
	int i;
	int j;
	int size;

	i = 0;
	size = 0;
	while (tab[size] != (void*)0)
		++size;
	j = size - 1;
	while (i < (size - 1))
	{
		j = size - 1;
		while (j > i)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
				ft_swap(&tab[i], &tab[j]);
			--j;
		}
		++i;
	}
}

int	is_mirrored_in_double_quotes(char c)
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

char	**env_to_array(t_env *env)
{
	t_env	*tmp;
	int	size;
	char	**names;

	tmp = env;
	size = 0;
	while((tmp = tmp->next))
		size++;
	names = (char**)malloc(sizeof(char*) * (size + 1));
	tmp = env;
	size = 0;
	while ((tmp = tmp->next))
	{
		if (tmp->name)
			names[size] = ft_strdup(tmp->name);
		size++;
	}
	names[size] = NULL;
	return (names);
}
