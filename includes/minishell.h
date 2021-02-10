/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:31:56 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/10 13:02:14 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# define STDIN	 1
# define STDOUT	 0

# define TRUE	 1
# define FALSE	 0
# define ERROR  -1
# define BOOL	int

typedef	struct		s_command
{
	char			*name;
	char			**args;
	char			**files;
	char 			*str;
	int				in;
	int 			out;
}					t_command;

//typedef	struct		s_commands
//{
//	t_command		*commands;
//	int				len;
//}					t_commands;

t_command	*get_parsed_command(char *str);
#endif
