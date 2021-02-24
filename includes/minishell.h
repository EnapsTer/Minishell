/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:31:56 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/15 18:02:34 by aherlind         ###   ########.fr       */
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
	// переписать используя t_fd
	int				in;
	int 			out;
}					t_command;

typedef struct		s_fd
{
	int 			in;
	int 			out;
}					t_fd;

t_command	*get_parsed_command(char *str);
#endif
