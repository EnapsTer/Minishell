/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_logic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:45:55 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/08 22:16:19 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include "start.h"

t_env	*add_env(t_env *begin, char *envp)
{
	char	*equal;
	t_env	*new;

	if (!(equal = ft_strchr(envp, '=')))
		return (begin);
	*equal++ = '\0';
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	if (!(new->name = ft_strdup(envp)))
	{
		free(new);
		return (NULL);
	}
	if (!(new->value = ft_strdup(equal)))
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	while (begin->next)
		begin = begin->next;
	begin->next = new;
}

t_env	*get_env(char **envp)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	if (!(env->name = ft_strdup("?")))
	{
		free(env);
		return (NULL);
	}
	if (!(env->value = ft_strdup("0")))
	{
		free(env->name);
		free(env);
		return (NULL);
	}
	env->next = NULL;
	while (*envp)
		if(!(add_env(env, *envp++)))
		{
			free_env(&env);
			return (NULL);
		}
	return (env);
}
