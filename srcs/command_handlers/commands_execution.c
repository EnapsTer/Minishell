/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:35:29 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/14 20:00:37 by aherlind         ###   ########.fr       */
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

BOOL 	is_builtin(char *str)
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

int g_pid;

BOOL handle_builtin(char **argv, t_env **envp, int commands_len)
{
	int	ret;
	pid_t	pid;

	ret = ERROR;
	pid = -1;
	if (commands_len > 1 && is_builtin(argv[0]))
	{
		if ((pid = fork()) <= ERROR)
		{
			print_error(0, strerror(errno));
			return (1);
		}
		if (pid != 0)
		{
			g_pid = pid;
			return (-2);
		}
	}
	if (!ft_strcmp(argv[0], "echo"))
		ret =  echo(argv);
	if (!ft_strcmp(argv[0], "cd"))
		ret = cd(argv, *envp);
	if (!ft_strcmp(argv[0], "env"))
		ret = env(*envp);
	if (!ft_strcmp(argv[0], "exit"))
		ret = ft_exit(argv);
	if (!ft_strcmp(argv[0], "export"))
		ret = ft_export(argv, envp);
	if (!ft_strcmp(argv[0], "pwd"))
		ret = pwd();
	if (!ft_strcmp(argv[0], "unset"))
		ret = unset(argv, *envp);
	if (ret != ERROR && pid == 0)
		exit(ret);
	return (ret);
}

int execute_command(t_command **commands, int i, t_env **env, int commands_len)
{
	pid_t		pid;
	char		*path;
	struct stat	file_stat;
	int 		ret;

	set_redirect(commands[i]);
	if ((ret = handle_builtin(commands[i]->args, env, commands_len)) == ERROR)
	{
		if ((pid = fork()) <= ERROR)
		{
			print_error(0, strerror(errno));
			return (1);
		}
		if (pid == 0)
		{
			if ((signal(SIGINT, SIG_DFL)) == SIG_ERR)
				print_error(0, "Error: Cannot catch SIGINT");
			if ((signal(SIGQUIT, SIG_DFL)) == SIG_ERR)
				print_error(0, "Error: Cannot catch SIGQUIT");
			close_pipe_fd(commands, i);
			if (!(path = get_command_path(commands[i]->args[0], env)))
				print_error_with_exit(commands[i]->args[0], "command not found", 127);
			if (stat(path, &file_stat) == ERROR)
				print_error_with_exit(path, strerror(errno), 127);
			if (execve(path, commands[i]->args, build_envp(env)) == ERROR) // free envp
				print_error_with_exit(path, strerror(errno), 126);
		}
		else
			g_pid = pid;
	}
	return (ret);
}

int 	get_commands_len(t_command **commands)
{
	int	len;

	len = 0;
	while (commands[len])
		len++;
	return (len);
}

int		execute_commands(t_command **commands, t_env **env)
{
	int 	i;
	int 	status;
	t_fd	stdfd;
	int 	ret;
	int 	commands_len;

	if (init_stdfd(&stdfd) == ERROR)
		return (ERROR);
	commands_len = get_commands_len(commands);
	i = 0;
	ret = -1;
	g_pid = 0;
	while (i < commands_len)
	{
		if (commands[i]->args)
			ret = execute_command(commands, i, env, commands_len);
		else
			return (ERROR);
		if (set_default_redirect(commands[i], &stdfd) == ERROR)
			return (ERROR); //print error
		i++;
	}
	int last_status;
//	printf("g_pid - %d\n", g_pid);
	while (waitpid(g_pid, &last_status, WUNTRACED) > 0)
		;
//		printf("last - %d\n", WEXITSTATUS(last_status));
	while (wait(&status) > 0)
		;
//		printf("wait - %d\n", WEXITSTATUS(status));
	if (ret == -1 || ret == -2)
		ret = WEXITSTATUS(last_status);
	return (ret);
}
