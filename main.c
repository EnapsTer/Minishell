/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/23 22:55:54 by nscarab          ###   ########.fr       */
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

// выводить errno
// exit code $?
// предварительный парсинг на ошибки ; ' "
// капс команды
// cat | ls
// тест на закрытие in fd пример
// echo "\$" ------ echo '\$'
//

int		g_int_fd;
size_t	g_input_lenght;
char	*g_input_str;

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

char	*read_commands(int *errors)
{
	int		count;
	char	buf[131072];

	g_input_str = NULL;
	g_input_lenght = 0;
	write(STDOUT, "minishell$ ", 11);
	while (1)
	{
		g_int_fd = dup(0);
		signal(SIGINT, signal_handle_read);
		signal(SIGQUIT, SIG_IGN);
		count = read (0, buf, 131071);
		//write (1, "1", 1);
		if (count >= 0)
		{
		g_input_lenght = g_input_lenght + count;
		//if (g_input_lenght > 131071)
			//return (NULL);
		buf[count] = '\0';
		if (g_input_lenght == 0)
		{
			g_input_str = ft_strdup("exit");
			write(STDOUT, "exit\n", 5);
		//write (1, "2", 1);
			return (g_input_str);
		}
		else if (buf[count - 1] == '\n')
		{
			buf[count - 1] = '\0';
			g_input_str = superstrjoin(g_input_str, buf);
		//write (1, "3", 1);
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

