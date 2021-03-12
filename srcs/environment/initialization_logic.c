/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_logic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:45:55 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/11 19:26:54 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include "start.h"

int	special_env(t_env **env)
{
	char *buf;

	buf = NULL;
	{
		if (is_env_declared("OLDPWD", *env))
			change_var_value("OLDPWD", &buf, env);
		else if (exp_new_var(env, "OLDPWD") > 0)
			return (1);
		if (!is_env_declared("SHLVL", *env))
		{
			if (!(buf = ft_strdup("SHLVL=1")))
				return (1);
			add_env(*env, buf);
			free(buf);
		}
		else
		{
			if (!(buf = ft_itoa(ft_atoi(get_env_value("SHLVL", env)) + 1)))
				return (1);
			change_var_value("SHLVL", &buf, env);
		}
	}
	return (0);
}

t_env	*create_env(char *name, char *value, t_env *next)
{
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	if (!(new->name = ft_strdup(name)))
	{
		free(new);
		return (NULL);
	}
	if (!value)
		new->value = NULL;
	else if (!(new->value = ft_strdup(value)))
	{
		free_env_elem(&new);
		return (NULL);
	}
	new->next = next;
	return (new);
}

void	put_env_back(t_env *new, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*add_env(t_env *env, char *envp)
{
	char	*equal;
	t_env	*new;

	if (!(equal = ft_strchr(envp, '=')))
		return (env);
	*equal++ = '\0';
	if (!(new = create_env(envp, equal, NULL)))
		return (NULL);
	put_env_back(new, env);
	return (env);
}

t_env	*get_env(char **envp)
{
	t_env	*env;

	if (!(env = create_env("?", "0", NULL)))
		return (NULL);
	while (*envp)
		if(!(add_env(env, *envp++)))
		{
			free_env(&env);
			return (NULL);
		}
	if ((special_env(&env)))
		{
			free_env(&env);
			return (NULL);
		}
	return (env);
}
