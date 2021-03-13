/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_sorted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:37:46 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/12 21:44:15 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start.h"
#include <libft.h>
#include "strs_utils.h"

void	print_names(char **names, t_env *env)
{
	int		i;
	char	*value;

	i = 0;
	while (names[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(names[i], 1);
		if ((value = get_env_value(names[i], &env)))
		{
			ft_putstr_fd("=", 1);
			putstr_export_fd(value, 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	ft_sort_array(char **tab)
{
	int	i;
	int	j;
	int	size;

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

char	**env_to_array(t_env *env)
{
	t_env	*tmp;
	int		size;
	char	**names;

	tmp = env;
	size = 0;
	while ((tmp = tmp->next))
		size++;
	if (!(names = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	tmp = env;
	size = 0;
	while ((tmp = tmp->next))
	{
		if (tmp->name)
			if (!(names[size] = ft_strdup(tmp->name)))
			{
				free_str_arr(&names);
				return (NULL);
			}
		size++;
	}
	names[size] = NULL;
	return (names);
}

int		print_sorted(t_env *env)
{
	char	**names;

	if (!(names = env_to_array(env)))
		return (1);
	ft_sort_array(names);
	print_names(names, env);
	free_str_arr(&names);
	return (0);
}
