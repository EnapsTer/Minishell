/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:10:49 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/11 18:35:32 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_H
#define START_H

///////////////////////////////
#include <libft.h>
///////////////////////////////

# define NEW_LINE		2
# define SYNTAX_ERROR		1
# define ALL_OK				0
# define RETURN_STR		-1
# define MALLOC_ERROR	-2

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
void	nullify_g_str(void);
void	nullify_str(char **buf);

/////////////errors_read//////////////

void	print_syntax_error(char *str, t_env **env, int *continue_flag);

/////////////signals_read//////////////

void	signal_handle_read(int signum);

/////////////syntax_utils//////////////

int	only_spaces_after(char *str, int i);
int	only_spaces_before(char *str, int i);
int	is_mirrored(char *str, int i);
int	ends_with_semicolon(char *str);

/////////////syntax_logic//////////////

char *remove_quoted_str(char *str, t_env **env, int *continue_flag);
int	is_semicoloned_syntax_correct(char *str);
int	is_string_error(char *str, t_env **env, int *continue_flag);
int	is_piped_syntax_correct(char *str);

/////////////environment_init_and_free//////////////

t_env	*get_env(char **envp);
t_env	*add_env(t_env *env, char *envp);
void	free_env_elem(t_env **env);
void	free_env(t_env **env);
t_env	*create_env(char *name, char *value, t_env *next);
void	put_env_back(t_env *new, t_env *env);

void	delete_env_var(char *name, t_env *env);
int	is_valid_env_name(char *str);
char	*get_env_value(char *name, t_env **env);
void	free_env_elem(t_env **env);
/////////////core_read_logic//////////////

int	read_commands(t_env **env);

/////////////handle_new_read_line//////////////

int	is_read_syntax_ok(int *continue_flag, t_env **env);

/////////////builtins_except_export//////////////

int	env(t_env *env);
int	echo(char **argv);
int	pwd(void);
int	cd(char **argv, t_env *env);
int	ft_exit(char **argv, int *flag);
int	ft_export(char **argv, t_env **env);
int	unset(char **argv, t_env *env);

/////////////export_builin//////////////

int	exp_new_var(t_env **env, char *str);
void	change_var_value(char *name, char **buf, t_env **env);
void	free_array(char ***array);
void	ft_sort_array(char **tab);
int	is_mirrored_in_double_quotes(char c);
char	**env_to_array(t_env *env);
void	print_names(char **names, t_env *env);
void	print_sorted(t_env *env);
int	ft_export(char **argv, t_env **env);
void	putstr_export_fd(char *str, int fd);
int	is_env_declared(char *name, t_env *env);
#endif
