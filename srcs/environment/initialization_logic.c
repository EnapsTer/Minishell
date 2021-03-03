/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_logic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:45:55 by nscarab           #+#    #+#             */
/*   Updated: 2021/02/28 17:49:22 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include "start.h"

void	add_env(t_env *begin, char *envp)
{
	char	*equal;
	t_env	*new;

	equal = ft_strchr(envp, '=');
	*equal++ = '\0';
	new = (t_env *)malloc(sizeof(t_env));
	new->name = ft_strdup(envp);
	new->value = ft_strdup(equal);
	new->next = NULL;
	while (begin->next)
		begin = begin->next;
	begin->next = new;
}

t_env	*get_env(char **envp)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->name = ft_strdup("?");
	env->value = ft_strdup("0");
	env->next = NULL;
	while (*envp)
	{
		add_env(env, *envp++);
	}
	return (env);
}
