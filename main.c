/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/26 15:03:37 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advanced_split.h"
#include "minishell.h"
#include "command_handlers.h"
#include "delimiter_comparators.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
///////////=============================================================////////////////
#include <libft.h>
#include <stdio.h>
#include <signal.h>
#include "start.h"
#include "strs_utils.h"

// выводить errno
// exit code $?
// предварительный парсинг на ошибки ; ' "
// капс команды
// cat | ls
// тест на закрытие in fd пример
// echo "\$" ------ echo '\$'
//

int		g_int_fd;
char	*g_input_str;


int	count_words(char **strs)
{
	int	count;

	count = 0;
	if (!strs)
		return(0);
	while (strs[count])
		count++;
	return (count);
}

int	ends_with_semicolon(char *str)
{
	int	count;

	count = 0;
	if(!str)
		return (0);
	while (str[count + 1])
		count++;
	if (str[count] == ';')
		return (1);
	//write(1, "n", 1);
	return (0);
}
int	ministrlen(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return(0);
	while (*str++)
		count++;
	return (count);
}

void	print_reading_error(char *str)
{
		write(STDOUT, str, ministrlen(str));
		if (g_input_str)
		{
		g_input_str[0] = '\0';
		//g_input_str = NULL; inache segi
		}
}

int	only_spaces_after(char *str, int i)
{
	if (!str)
		return (1);
	while (str[++i])
	{
		if (str[i] != ' ' || str[i] != '\t')
			return (0);
	}
	return (1);
}

int	only_spaces_before(char *str, int i)
{
	if (!str)
		return (1);
	while (--i >= 0)
	{
		if (str[i] != ' ' || str[i] != '\t')
			return (0);
	}
	return (1);
}

int	is_mirrored(char *str, int i)
{
	int	count;

	count = 0;
	while (--i >= 0)
		{
			if (str[i] == '\\')
				count++;
			else
				break;
		}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

char	*superstrjoin(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	i;
	char	*cs1;

	cs1 = s1;
	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	i = 0;
	result = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1 && *s1)
		result[i++] = *s1++;
	while (s2 && *s2)
		result[i++] = *s2++;
	result[i] = '\0';
	if (cs1)
		free(cs1);
	return (result);
}

void	signal_handle_read(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT, "\b\b  \b\b\nminishell$ ", 18);
		close(0);
		//g_input_fd = -1;
		//g_input_lenght = 0;
		if (g_input_str)
		{
		g_input_str[0] = '\0';
		g_input_str = NULL;
		}
	}
	if (signum == SIGQUIT)
		write(STDOUT, "\b\b  \b\b", 6);
}

int	is_semicoloned_syntax_correct(char *str)
{
	int	count;

	count = 0;
	if (only_spaces_after(str, -1))
			return (0);
				//write (1, "8", 1);
	while (str[count])
	{
		if ((str[count] == '>' || str[count] == '<'|| str[count] == '|')
					&& !(is_mirrored(str, count)) &&
					only_spaces_after(str, count))
		return (0);
		count++;
	}
	return (1);
}

int	is_piped_syntax_correct(char *str)
{
	int	count;

	count = 0;
	if (only_spaces_after(str, -1))
			return (0);
	while (str[count])
	{
		if ((str[count] == '>' || str[count] == '<')
					&& !(is_mirrored(str, count)) &&
					only_spaces_after(str, count))
		return (0);
		count++;
	}
	return (1);
}

char	*read_commands(int *errors)
{
	int		count;
	int		strlen;
	char	buf[131072];

	g_input_str = NULL;
	strlen = 0;
	write(STDOUT, "minishell$ ", 11);
	g_int_fd = dup(0);
	while (1)
	{
		signal(SIGINT, signal_handle_read);
		signal(SIGQUIT, SIG_IGN);
		count = read (0, buf, 131071);
		//write (1, "1", 1);
		if (count >= 0)
		{
			strlen = ministrlen(g_input_str) + count;
			//if (g_input_lenght > 131071)
			//return (NULL);
			buf[count] = '\0';
			if (strlen == 0)
			{
				g_input_str = ft_strdup("exit");
				write(STDOUT, "exit\n", 5);
				//write (1, "2", 1);
				return (g_input_str);
			}
			else if (buf[count - 1] == '\n')
			{
				buf[count - 1] = '\0';
				strlen--;
				g_input_str = superstrjoin(g_input_str, buf);
				//////////////////////////////////////////////////////check/////////////
				char		**semicoloned_strs;
				char		**piped_strs;
				int			i;
				int 		j;
				int		continue_flag;
				int		last_flag;
				continue_flag = 0;
				
				semicoloned_strs = ft_split(g_input_str, ';');
				printf("%s\n", g_input_str);
	//semicoloned_strs = advanced_split(ft_strdup(g_input_str), is_semicolon, 0);
					//printf("%s\n", semicoloned_strs[0]);
				//words = count_words(semicoloned_strs);
				last_flag = !ends_with_semicolon(g_input_str);
				i = 0;
				while (semicoloned_strs[i])
				{
					printf("%s, %d\n", semicoloned_strs[i], i);
					i++;
				}
				i = 0;
				while (semicoloned_strs[i]  && semicoloned_strs[i + last_flag]
							&& continue_flag == 0)
				{
				//write (1, "3", 1);
					//printf("%s\n", semicoloned_strs[i]);
					if (!(is_semicoloned_syntax_correct(semicoloned_strs[i])))
					{
						print_reading_error("bash: syntax error near unexpected token `;'\n");
						write(STDOUT, "minishell$ ", 11);
						continue_flag = 1;
					}
				//write (1, "4", 1);
					if (!(piped_strs = ft_split(semicoloned_strs[i], '|')))
						return (NULL);
					//if (!(piped_strs = advanced_split(semicoloned_strs[i], is_pipe, 0)))
					j = -1;	
					while (piped_strs[++j] && continue_flag == 0)
					{
				//write (1, "5", 1);
					//printf("%s\n", piped_strs[j]);
						if (!(is_piped_syntax_correct(piped_strs[j])))
						{
							print_reading_error("bash: syntax error near unexpected token `|'\n");
							write(STDOUT, "minishell$ ", 11);
							continue_flag = 1;
						}
					}
					free_str_arr(&piped_strs);
					++i;
				}
				free_str_arr(&semicoloned_strs);
				int 		count;
				count = 0;
				while (last_flag  &&
						g_input_str[count] && continue_flag == 0)
				{
					if ((g_input_str[count] == '>' || g_input_str[count] == '<')
							&& !(is_mirrored(g_input_str, count)) &&
							only_spaces_after(g_input_str, count))
					{
						print_reading_error("bash: syntax error near unexpected token `newline'\n");
						write(STDOUT, "minishell$ ", 11);
						continue_flag = 1;
					}
					if (g_input_str[count] == '|' && !(is_mirrored(g_input_str, count)) &&
							only_spaces_after(g_input_str, count))
					{
						continue_flag = 1;
						write (1, "> ", 2);
					}
					count++;
				}
				///////////////////////////////////////////////////////////////////////////
				if (continue_flag)
					continue;
				return (g_input_str);
			}
			else
			{
				write(STDOUT, "  \b\b", 4);
				g_input_str = superstrjoin(g_input_str, buf);
				//write (1, "4", 1);
				continue;
			}
		}
		else
			dup2(g_int_fd, 0);
	}
}


void	signal_handle_routine(int signum)
{
	if (signum == SIGQUIT)
		write(STDOUT, "Quit: 3", 7);
	write(STDOUT, "\n", 1);
}

void	routine (t_env **env)
{
	char	*str;
	int		errors;

	while (1)
	{
		str = read_commands(&errors);
		signal(SIGINT, signal_handle_routine);
		signal(SIGQUIT, signal_handle_routine);
		//printf("%s\n", str);
		handle_commands(str, env);
		if (str)
			free(str);
	}
}

void	add_env(t_env *begin, char *envp)
{
	char	*equal;
	t_env	*new;

	equal = ft_strchr(envp, '=');
	*equal++ = '\0';
	new = (t_env *)malloc(sizeof(t_env));
	new->name = ft_strdup(envp);
	new->value = ft_strdup(equal);
	new->next = NULL;
	while (begin->next)
		begin = begin->next;
	begin->next = new;
}

t_env	*get_env(char **envp)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->name = ft_strdup("?");
	env->value = ft_strdup("0");
	env->next = NULL;
	while (*envp)
	{
		add_env(env, *envp++);
	}
	return (env);
}

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*begin;

	begin = *env;
	while (*env)
	{
		if ((*env)->name)
		{
			free((*env)->name);
			(*env)->name = NULL;
		}
		if ((*env)->value)
		{
			free((*env)->value);
			(*env)->value = NULL;
		}
		tmp = *env;
		*env = tmp->next;
		free(tmp);
	}
	begin = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_env *env;

	env = get_env(envp);
	///////////////////print env////////////////////////////
	//t_env *begin;
	//begin = env;
	//while (env->next)
	//{
		//printf("%s|||%s\n", env->name, env->value);
		//env = env->next;
	//}
	//printf("%s|||%s\n", env->name, env->value);
	//env = begin;
	///////////////////print env////////////////////////////
	routine(&env);
	//предварительный парсинг
	free_env(&env);
	return (0);
}

