/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:35:29 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/21 20:22:32 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment_utils.h"
#include "libft.h"
#include "delimiter_comparators.h"
#include "advanced_split.h"
#include "strs_utils.h"
#include "commands_utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "start.h"
#include "environment_utils.h"


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

// STDIN - 0 ==== stdin
// STDOUT - 1 ===
// file1 - 3  === file1

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
	// cat 0 4  ---  ls 3 1
	if (commands[i + 1] && commands[i]->out != STDOUT && commands[i + 1]->in != STDIN)
		close(commands[i + 1]->in);
	return (TRUE);
}

int execute_command(t_command **commands, int i, t_env **env)
{
	pid_t	pid;
	char 	*path;

	set_redirect(commands[i]);
	if ((pid = fork()) <= ERROR)
		return (ERROR);
	if (pid == 0)
	{
		if (!(path = get_command_path(commands[i]->args[0], env)))
			exit(1);
		//error
		// cat | ls
		//echo 1234 qwerty
		close_pipe_fd(commands, i);
		if (execve(path, commands[i]->args, build_envp(env)) == ERROR)
			return (ERROR);

	}
	return (TRUE);
}


int		execute_commands(t_command **commands, t_env **env)
{
	int 	i;
	int 	status;
	t_fd	stdfd;

	if (init_stdfd(&stdfd) == ERROR)
		return (ERROR);
	i = 0;
	// echo hello > file1 | ls
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
	return (TRUE);
}
