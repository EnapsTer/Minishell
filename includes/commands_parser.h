/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:07:18 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 18:29:59 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_PARSER_H
# define COMMANDS_PARSER_H
# include "minishell.h"

int		parse_command(char *str, t_command *command, t_env *env);

#endif
