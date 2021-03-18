/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:53:56 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 17:54:13 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_EXECUTION_H
# define COMMANDS_EXECUTION_H
# include "start.h"

int		execute_commands(t_command **commands, t_env **env);

char	*get_command_path(char *name, t_env **env);

int		get_commands_len(t_command **commands);

int		set_redirect(t_command *command);

int		set_default_redirect(t_command *command, t_fd *stdfd);

int		close_pipe_fd(t_command **commands, int i);

BOOL	is_builtin(char *str);

int		run_builtin(char **argv, t_env **envp);

#endif
