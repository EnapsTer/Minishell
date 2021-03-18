/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:27:17 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 17:31:34 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "commands_execution.h"
#include "strs_utils.h"
#include <unistd.h>
#include "start.h"

int		run_builtin(char **argv, t_env **envp)
{
	int	ret;

	ret = ERROR;
	if (!ft_unregister_strcmp(argv[0], "echo"))
		ret = echo(argv);
	else if (!ft_strcmp(argv[0], "cd"))
		ret = cd(argv, *envp);
	else if (!ft_unregister_strcmp(argv[0], "env"))
		ret = env(*envp);
	else if (!ft_strcmp(argv[0], "exit"))
		ret = ft_exit(argv);
	else if (!ft_strcmp(argv[0], "export"))
		ret = ft_export(argv, envp);
	else if (!ft_unregister_strcmp(argv[0], "pwd"))
		ret = pwd();
	else if (!ft_strcmp(argv[0], "unset"))
		ret = unset(argv, *envp);
	return (ret);
}

int		set_redirect(t_command *command)
{
	if (command->in != STDIN)
	{
		if (dup2(command->in, STDIN) == ERROR)
			return (ERROR);
	}
	if (command->out != STDOUT)
	{
		if (dup2(command->out, STDOUT) == ERROR)
			return (ERROR);
	}
	return (TRUE);
}

int		set_default_redirect(t_command *command, t_fd *stdfd)
{
	if (command->in != STDIN)
	{
		if (close(command->in) < 0)
			return (ERROR);
		if (dup2(stdfd->in, STDIN) == ERROR)
			return (ERROR);
	}
	if (command->out != STDOUT)
	{
		if (close(command->out) < 0)
			return (ERROR);
		if (dup2(stdfd->out, STDOUT) == ERROR)
			return (ERROR);
	}
	return (TRUE);
}

int		close_pipe_fd(t_command **commands, int i)
{
	if (i > 0 && commands[i]->in != STDIN && commands[i - 1]->out != STDOUT)
		close(commands[i - 1]->out);
	if (commands[i + 1] && commands[i]->out != STDOUT &&
									commands[i + 1]->in != STDIN)
		close(commands[i + 1]->in);
	return (TRUE);
}

BOOL	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (TRUE);
	if (!ft_strcmp(str, "cd"))
		return (TRUE);
	if (!ft_strcmp(str, "env"))
		return (TRUE);
	if (!ft_strcmp(str, "exit"))
		return (TRUE);
	if (!ft_strcmp(str, "export"))
		return (TRUE);
	if (!ft_strcmp(str, "pwd"))
		return (TRUE);
	if (!ft_strcmp(str, "unset"))
		return (TRUE);
	return (FALSE);
}
