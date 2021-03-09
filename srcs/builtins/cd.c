/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:31:30 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/05 18:38:32 by nscarab          ###   ########.fr       */
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

	buf = NULL;
	if (!getcwd(buf, 0))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}
	if (get_env_value("OLDPWD", &env))
		change_var_value("OLDPWD", &buf, &env);
	if (!argv[1])
	{
		path = get_env_value("HOME", &env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set", 2);
			exit (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}
	if (!getcwd(buf, 0))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}
	if (get_env_value("PWD", &env))
		change_var_value("PWD", &buf, &env);
	exit (0);
}
