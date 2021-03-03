/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:10:49 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/02 15:44:34 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_H
#define START_H

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

extern char	*g_input_str;
extern int	g_int_fd;


/////////////read_utils//////////////

char	*superstrjoin(char *s1, char *s2);
int	ministrlen(char *str);
void	strzero(char *str);

/////////////errors_read//////////////

void	print_reading_error(char *str);

/////////////signals_read//////////////

void	signal_handle_read(int signum);

/////////////syntax_utils//////////////

int	only_spaces_after(char *str, int i);
int	only_spaces_before(char *str, int i);
int	is_mirrored(char *str, int i);
int	ends_with_semicolon(char *str);

/////////////syntax_logic//////////////

int	is_semicoloned_syntax_correct(char *str);
int	is_string_error(char *str);
int	is_piped_syntax_correct(char *str);

/////////////environment_init_and_free//////////////

t_env	*get_env(char **envp);
void	add_env(t_env *begin, char *envp);
void	free_env(t_env **env);

/////////////core_read_logic//////////////

int	handle_new_line(int *continue_flag, char (*buf)[131072], int count);
void	read_init(void);
void	exit_shell_from_read(void);
void	continue_read_after_eof(int *continue_flag, char buf[131072]);
char	*read_commands(int *errors);

/////////////handle_new_read_line//////////////

int	handle_end_of_string(int *continue_flag);
void	handle_semicoloned_syntax(int *continue_flag, char *str);
void	handle_piped_syntax(int *continue_flag, char *str, int last_open);
int	is_read_syntax_ok(int *continue_flag);
#endif
