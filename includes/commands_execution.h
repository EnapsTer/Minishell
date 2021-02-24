/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:53:56 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/21 19:58:41 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_EXECUTION_H
#define COMMANDS_EXECUTION_H

#include "start.h"
int execute_command(t_command *command, t_env **env, t_fd *stdenv);

int		execute_commands(t_command **commands, t_env **env);
#endif
