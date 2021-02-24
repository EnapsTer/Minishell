/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:59:09 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/21 19:58:41 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
#define COMMANDS_H
#include "minishell.h"
#include "start.h"

int handle_commands(char *str, t_env **env);

int			handle_redirects(t_command *command);

int 		handle_pipes(t_command **commands);


#endif
