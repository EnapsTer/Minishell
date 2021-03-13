/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_deletion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:10:12 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/13 11:18:11 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start.h"
#include <stdlib.h>
#include "libft.h"

void	free_env_elem(t_env **env)
{
	if ((*env)->name)
	{
		free((*env)->name);
		(*env)->name = NULL;
	}
	if ((*env)->value)
	{
		free((*env)->value);
		(*env)->value = NULL;
	}
	if ((*env))
	{
		free((*env));
		(*env) = NULL;
	}
}

void	delete_env_var(char *name, t_env *env)
{
	t_env	*cur;
	t_env	*prev;

	prev = NULL;
	cur = env;
	while (cur)
	{
		if (!ft_strcmp(name, cur->name))
		{
			prev->next = cur->next;
			free_env_elem(&cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = tmp->next;
		free_env_elem(&tmp);
	}
}
