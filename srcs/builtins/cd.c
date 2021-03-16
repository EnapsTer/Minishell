/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:31:30 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/12 22:07:00 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <libft.h>
#include "start.h"
#include <stdlib.h>

static int	handle_pwd(t_env *env)
{
	char	*buf;
	int		out;

	out = 0;
	if (!(buf = getcwd(NULL, 0)))
	{
		ft_putstr_fd("minishell: cd: getcwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	else if (is_env_declared("PWD", env))
		change_var_value("PWD", &buf, &env);
	else
		free(buf);
	return (out);
}

static int	handle_oldpwd(t_env *env)
{
	char	*buf;
	int		out;

	out = 0;
	if (!(buf = getcwd(NULL, 0)))
	{
		ft_putstr_fd("minishell: cd: getcwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		out = 1;
	}
	else if (is_env_declared("OLDPWD", env))
		change_var_value("OLDPWD", &buf, &env);
	else
		free(buf);
	return (out);
}

static char	*get_path(char **argv, t_env *env)
{
	char	*path;

	if (!argv[1])
	{
		path = get_env_value("HOME", &env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		path = argv[1];
	return (path);
}

int			cd(char **argv, t_env *env)
{
	char	*path;
	int		out;

	out = 0;
	out = handle_oldpwd(env);
	if (!(path = get_path(argv, env)))
		return (1);
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	out = handle_pwd(env);
	return (out);
}
