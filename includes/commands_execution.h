/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:53:56 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/13 13:46:25 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_EXECUTION_H
#define COMMANDS_EXECUTION_H

int execute_command(t_command *command, char **envp, t_fd *stdenv);

int		execute_commands(t_command **commands, char **envp);
#endif
