/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:07:18 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/03 12:17:52 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROJECT_COMMANDS_PARSER_H
#define MINISHELL_PROJECT_COMMANDS_PARSER_H
# include "minishell.h"

t_command get_parsed_commands(char *str);

int 		parse_command(char *str, t_command *command);



#endif