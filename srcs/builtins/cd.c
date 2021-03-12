/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:31:30 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/10 21:28:48 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <libft.h>
#include "start.h"
#include <stdlib.h>

int	cd(char **argv, t_env *env)
{
	char	*buf;
	char	*path;
	int	out;

	out = 0;
	if (!(buf = getcwd(NULL, 0)))
	{
		ft_putstr_fd("minishell: cd: getcwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		out = 1;
	}
	else if (is_env_declared("OLDPWD", env))
		change_var_value("OLDPWD", &buf, &env);
	if (!argv[1])
	{
		path = get_env_value("HOME", &env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);;
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (!(buf = getcwd(NULL, 0)))
	{
		ft_putstr_fd("minishell: cd: getcwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (is_env_declared("PWD", env))
		change_var_value("PWD", &buf, &env);
	return (out);
}
