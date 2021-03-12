/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:11:45 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/11 18:36:19 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start.h"
#include <libft.h>
#include "strs_utils.h"

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
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	print_sorted(t_env *env)
{
	char	**names;

	names = env_to_array(env);
	ft_sort_array(names);
	print_names(names, env);
	free_str_arr(&names);
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
				nullify_str(&tmp_c);
			return ;
		}
		tmp = (tmp)->next;
	}
	nullify_str(buf);
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
		return (1);
	if (!is_env_declared(str, *env))
	{
		if (!(new = create_env(str, equal, NULL)))
			return (2);
		put_env_back(new, *env);
	}
	else if (equal)
	{
		if (!(equal = ft_strdup(equal)))
			return (2);
		change_var_value(str, &equal, env);
	}
	return (0);
}

void	print_export_error(char *argv, char *describe)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(describe, 2);
}

int	ft_export(char **argv, t_env **env)
{
	int	count;
	int	out;
	int	err;

	count = 1;
	out = 0;
	if (!argv[1])
	{
		print_sorted(*env);
		return (out);
	}
	while (argv[count])
	{
		err = exp_new_var(env, argv[count]);
		if (err == 1)
			print_export_error(argv[count], "not a valid identifier");
		else if (err == 2)
			print_export_error(argv[count], "Cannot allocate memory");
		if (err > 0)
			out = 1;
		count++;
	}
	return (out);
}
