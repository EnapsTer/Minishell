/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:35:29 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/13 16:54:42 by aherlind         ###   ########.fr       */
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
char 	*get_command_path(char *name, char **envp)
{
	char 	*path;
	char 	**env_path;
	int 	i;

	if (ft_strchr(name, '/'))
		return (name);
	i = 0;
	if (!(env_path = advanced_split(get_env_value("PATH", envp), is_colon, 0)))
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

int set_default_redirect(t_command *command, t_stdfd *stdfd)
{
	if (command->in != STDIN)
	{
		if (close(command->in) < 0)
			return (ERROR);
		if (dup2(stdfd->std_in, STDIN) == ERROR)
			return (ERROR);
	}
	if (command->out != STDOUT)
	{
		if (close(command->out) < 0)
			return (ERROR);
		if (dup2(stdfd->std_out, STDOUT) == ERROR)
			return (ERROR);

	}
}
// echo 123 > file1 > file2
int execute_command(t_command *command, char **envp, t_stdfd *stdfd)
{
	pid_t	pid;
	char 	*path;

	set_redirect(command);
	if ((pid = fork()) <= ERROR)
		return (ERROR);
	if (pid == 0)
	{
		if (!(path = get_command_path(command->args[0], envp)))
			exit(1); // доделать
		execve(path, command->args, envp);
	}
	set_default_redirect(command, stdfd);
	return (TRUE);
}

int		execute_commands(t_command **commands, char **envp)
{
	int 	i;
	int 	status;
	t_stdfd stdfd;

	if (init_stdfd(&stdfd) == ERROR)
		return (ERROR);
	i = 0;
	while (commands[i])
	{
		execute_command(commands[i], envp, &stdfd);
		i++;
	}
	while (wait(&status) > 0)
		;
	return (TRUE);
}