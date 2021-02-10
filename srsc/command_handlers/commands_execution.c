/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:35:29 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/10 13:38:59 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int		execute_command(t_command *command, char **envp)
{
	int		old_stdin;
	int 	old_stdout;
	int 	status;
	pid_t	pid;

	old_stdin = dup(STDIN);
	old_stdout = dup(STDOUT);
	if ((pid = fork()) <= ERROR)
		return (ERROR);
	if (pid == 0)
	{
		execve(command->name, command->args, envp);
	}
	while (wait(&status) > 0)
		;
	return (TRUE);
}