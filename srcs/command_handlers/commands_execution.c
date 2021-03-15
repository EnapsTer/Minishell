/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:35:29 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 20:15:33 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "commands_execution.h"
#include "strs_utils.h"
#include "commands_utils.h"
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include "start.h"
#include "environment_utils.h"
#include "print_errors.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

BOOL	handle_builtin(char **argv, int *last_pid,
					int commands_len, t_env **envp)
{
	int		ret;
	pid_t	pid;

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
			*last_pid = pid;
			return (-2);
		}
	}
	ret = run_builtin(argv, envp);
	if (ret != ERROR && pid == 0)
		exit(ret);
	return (ret);
}

void	execution_process(char **argv, t_env **env)
{
	char		*path;
	struct stat	file_stat;
	char		**envp;

	envp = build_envp(env);
	if ((signal(SIGINT, SIG_DFL)) == SIG_ERR)
		print_error(0, "Error: Cannot catch SIGINT");
	if ((signal(SIGQUIT, SIG_DFL)) == SIG_ERR)
		print_error(0, "Error: Cannot catch SIGQUIT");
	if (!(path = get_command_path(argv[0], env)))
	{
		free_str_arr(&envp);
		print_error_with_exit(argv[0], "command not found", 127);
	}
	if (stat(path, &file_stat) == ERROR)
		print_error_with_exit(path, strerror(errno), 127);
//	if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
//		print_error_with_exit(path, "is a directory", 126);
	if (execve(path, argv, envp) == ERROR)
		print_error_with_exit(path, strerror(errno), 126);
	free_str_arr(&envp);
}

int		execute_command(t_command **commands, int i, int *last_pid, t_env **env)
{
	pid_t	pid;
	int		ret;

	set_redirect(commands[i]);
	if ((ret = handle_builtin(commands[i]->args, last_pid,
									get_commands_len(commands), env)) == ERROR)
	{
		if ((pid = fork()) <= ERROR)
		{
			print_error(0, strerror(errno));
			return (1);
		}
		if (pid == 0)
		{
			close_pipe_fd(commands, i);
			execution_process(commands[i]->args, env);
		}
		else
			*last_pid = pid;
	}
	return (ret);
}

int		wait_processes(int ret, int last_pid)
{
	int status;

	while (waitpid(last_pid, &status, WUNTRACED) > 0)
		;
	while (wait(NULL) > 0)
		;
	if (ret == -1 || ret == -2)
		ret = WEXITSTATUS(status);
	return (ret);
}

int		execute_commands(t_command **commands, t_env **env)
{
	int		i;
	t_fd	stdfd;
	int		ret;
	int		commands_len;
	int		last_pid;

	if (init_stdfd(&stdfd) == ERROR)
		return (ERROR);
	commands_len = get_commands_len(commands);
	i = -1;
	ret = -1;
	last_pid = 0;
	while (++i < commands_len)
	{
		if (commands[i]->args)
			ret = execute_command(commands, i, &last_pid, env);
		else
			return (ERROR);
		if (set_default_redirect(commands[i], &stdfd) == ERROR)
		{
			print_error(0, strerror(errno));
			return (ERROR);
		}
	}
	return (wait_processes(ret, last_pid));
}
