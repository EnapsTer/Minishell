/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:11:45 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/12 15:18:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start.h"
#include <libft.h>

void	print_names(char **names, t_env *env)
{
	int	i;
	char	*value;

	i = 0;
	while (names[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(names[i], 1);
		if((value = get_env_value(names[i], &env)))
		{
			ft_putstr_fd("=", 1);
			putstr_export_fd(value, 1);
			ft_putstr_fd("\n", 1);
		}
	}
}

void	print_sorted(t_env *env)
{
	char	**names;

	names = env_to_array(env);
	ft_sort_array(names);
	print_names(names, env);
	free_array(&names);
}

void	change_var_value(char *name, char **buf, t_env **env)
{
	t_env	*tmp;
	char	*tmp_c;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name, (tmp)->name))
		{
			tmp_c = tmp->value;
			(tmp)->value = *buf;
			if (tmp_c)
				free(tmp_c);
			return ;
		}
		tmp = (tmp)->next;
	}
	free(*buf);
	*buf = NULL;
}

int	is_env_declared(char *name, t_env *env)
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

int	exp_new_var(t_env **env, char *str)
{
	char	*equal;
	t_env	*new;
	t_env	*tmp;

	tmp = *env;
	if ((equal = ft_strchr(str, '=')))
		*equal++ = '\0';
	if (!is_valid_env_name(str))
		return (-1);
	if (!is_env_declared(str, *env))
	{
		new = (t_env *)malloc(sizeof(t_env));
		new->name = ft_strdup(str);
		if (equal)
			new->value = ft_strdup(equal);
		else
			new->value = NULL;
		new->next = NULL;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		if (equal)
		{
			equal = ft_strdup(equal);
			change_var_value(str, &equal, env);
		}
	return (0);
}

int	ft_export(char **argv, t_env **env)
{
	int	count;
	int	out;

	count = 0;
	out = 0;
	if (!argv[1])
		print_sorted(*env);
	while (argv[count])
	{
		if (!exp_new_var(env, argv[count]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[count], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			out = 1;
			continue;
		}
		count++;
	}
	return (out);
}
