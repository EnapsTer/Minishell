/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:31:56 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/03 12:17:52 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define BOOL int

typedef	struct		s_command
{
	char			*name;
	char			**args;
	char			**files;
	int				in;
	int 			out;
}					t_command;

t_command get_parsed_commands(char *str); //delete
#endif
