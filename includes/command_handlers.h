/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:59:09 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 18:26:12 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HANDLERS_H
# define COMMAND_HANDLERS_H
# include "minishell.h"
# include "start.h"

int			handle_commands(char *str, t_env **env);

int			handle_redirects(t_command *command);

int			handle_pipes(t_command **commands);

t_command	*get_parsed_command(char *str, t_env *env);

#endif
