/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:03:26 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/18 19:43:26 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "advanced_split.h"
#include "libft.h"
#include "strs_utils.h"
#include "delimiter_comparators.h"
#include <stdlib.h>
#include "start.h"

int		is_valid_env_name(char *str)
{
	if (!*str)
		return (0);
	if (ft_isdigit(str[0]))
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str) && !ft_isalpha(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

char	*get_envp_value(char *name, char **envp)
{
	int		i;
	char	**strs;
	char	*result;

	i = 0;
	while (envp[i])
	{
		if (!(strs = advanced_split(envp[i], is_equal, 0)))
			return (NULL);
		if (!ft_strcmp(name, strs[0]))
		{
			result = ft_strdup(strs[1]);
			free_str_arr(&strs);
			return (result);
		}
		free_str_arr(&strs);
		i++;
	}
	return (NULL);
}

char	*get_env_value(char *name, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name, (tmp)->name))
			return ((tmp)->value);
		tmp = (tmp)->next;
	}
	return (NULL);
}

char	**build_envp(t_env **env)
{
	int		size;
	t_env	*tmp;
	char	**result;

	tmp = *env;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	result = (char**)malloc(sizeof(char*) * (size + 1));
	tmp = *env;
	size = 0;
	while (tmp)
	{
		if (tmp->value)
			result[size++] =
					superstrjoin(ft_strjoin(tmp->name, "="), tmp->value);
		tmp = tmp->next;
	}
	result[size] = NULL;
	return (result);
}
