/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:31:56 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 18:23:49 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define STDIN	 0
# define STDOUT	 1
# define STDERROR 2
# define TRUE	 1
# define FALSE	 0
# define ERROR  -1
# define SKIP	-2
# define BOOL	int

typedef	struct		s_command
{
	char			**args;
	char			**files;
	char			*str;
	int				in;
	int				out;
}					t_command;

typedef struct		s_fd
{
	int				in;
	int				out;
}					t_fd;

#endif
