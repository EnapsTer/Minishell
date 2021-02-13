/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:31:56 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/13 13:45:13 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# define STDIN	 0
# define STDOUT	 1

# define TRUE	 1
# define FALSE	 0
# define ERROR  -1
# define BOOL	int

typedef	struct		s_command
{
	char			**args;
	char			**files;
	char 			*str;
	int				in;
	int 			out;
}					t_command;

typedef struct		s_stdfd
{
	int 			std_in;
	int 			std_out;
}					t_stdfd;

//typedef	struct		s_commands
//{
//	t_command		*commands;
//	int				len;
//}					t_commands;

t_command	*get_parsed_command(char *str);
#endif
