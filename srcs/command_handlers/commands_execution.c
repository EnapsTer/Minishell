/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:35:29 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/12 15:18:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "delimiter_comparators.h"
#include "advanced_split.h"
#include "strs_utils.h"
#include "commands_utils.h"
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "start.h"
#include "environment_utils.h"
#include "print_errors.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int 	is_in_directory(char *file_name, char *path)
{
	DIR				*dir;
	struct dirent	*dir_file;

	if (!(dir = opendir(path)))
		return (ERROR);
	while ((dir_file = readdir(dir)))
	{
		if (!ft_strcmp(file_name, dir_file->d_name))
		{
			closedir(dir);
			return (TRUE);
		}
	}
	closedir(dir);
	return (FALSE);
}


//переписать
char	*create_full_path(char *name, char *path)
{
	char	*result;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(path) + 1;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(result, path, len + 1);
	ft_strlcat(result, "/", len + 1);
	ft_strlcat(result, name, len + 1);
	return (result);
}

//возможно перенести функцию
char 	*get_command_path(char *name, t_env **env)
{
	char 	*path;
	char 	**env_path;
	int 	i;

	if (ft_strchr(name, '/'))
		return (name);
	i = 0;
	if (!(env_path = advanced_split(get_env_value("PATH", env), is_colon, 0)))
		return (NULL);
	while (env_path[i])
	{
		if (is_in_directory(name, env_path[i]))
		{
			if (!(path = create_full_path(name, env_path[i])))
				return (NULL);
			free_str_arr(&env_path);
			return (path);
		}
		i++;
	}
	free_str_arr(&env_path);
	return (NULL);
}

int set_redirect(t_command *command)
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

int set_default_redirect(t_command *command, t_fd *stdfd)
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
	if (commands[i + 1] && commands[i]->out != STDOUT && commands[i + 1]->in != STDIN)
		close(commands[i + 1]->in);
	return (TRUE);
}

BOOL		is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (TRUE);
	if (!ft_strcmp(name, "cd"))
		return (TRUE);
	if (!ft_strcmp(name, "env"))
		return (TRUE);
	if (!ft_strcmp(name, "exit"))
		return (TRUE);
	if (!ft_strcmp(name, "export"))
		return (TRUE);
	if (!ft_strcmp(name, "pwd"))
		return (TRUE);
	if (!ft_strcmp(name, "unset"))
		return (TRUE);
	return (FALSE);
}

BOOL		run_builtin(char **argv, t_env **envp)
{
	int *exit_flag = NULL;
	if (!ft_strcmp(argv[0], "echo"))
		return (echo(argv));
	if (!ft_strcmp(argv[0], "cd"))
		return (cd(argv, *envp));
	if (!ft_strcmp(argv[0], "env"))
		return (env(*envp));
	if (!ft_strcmp(argv[0], "exit"))
		return (ft_exit(argv, exit_flag));
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv, envp));
	if (!ft_strcmp(argv[0], "pwd"))
		return (pwd());
	if (!ft_strcmp(argv[0], "unset"))
		return (unset(argv, *envp));
	return (FALSE);
}

int execute_command(t_command **commands, int i, t_env **env)
{
	pid_t		pid;
	char		*path;
	struct stat	file_stat;

	set_redirect(commands[i]);
//	if (commands[i]->args)
//	{
//		if (is_builtin(commands[i]->args[0]))
//		{
//			run_builtin(commands[i]->args, env);
//		}
//		else
//		{
			if ((pid = fork()) <= ERROR)
				return (ERROR);
			if (pid == 0)
			{
				close_pipe_fd(commands, i);
				if (!(path = get_command_path(commands[i]->args[0], env)))
				{
					print_error_with_exit(path, "command not found", 127);
				}
				if (stat(path, &file_stat) == ERROR)
					print_error_with_exit(path, strerror(errno), 127);
				if (execve(path, commands[i]->args, build_envp(env)) == ERROR)
					print_error_with_exit(path, strerror(errno), 126);
			}
//		}
//	}
	return (TRUE);
}


int		execute_commands(t_command **commands, t_env **env)
{
	int 	i;
	int 	status;
	t_fd	stdfd;
	int 	ret;

	if (init_stdfd(&stdfd) == ERROR)
		return (ERROR);
	i = 0;
	while (commands[i])
	{
		if (execute_command(commands, i, env) == ERROR)
			return (ERROR);
		if (set_default_redirect(commands[i], &stdfd) == ERROR)
			return (ERROR);
		i++;
	}
	while (wait(&status) > 0)
		;
	ret = WEXITSTATUS(status);
	return (ret);
}
