/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:42:43 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/09 16:51:06 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "advanced_split.h"
#include "environment_utils.h"
#include "start.h"
#include "delimiter_comparators.h"
#include "strs_utils.h"

#include <stdio.h>

int 		skip_delimiters(char **str)
{
	BOOL	redirect_flag;

	redirect_flag = FALSE;
	while (**str && is_redirect_and_space(*str))
	{
		if (is_redirect(*str))
			redirect_flag = TRUE;
		(*str)++;
	}
	return (redirect_flag);
}

char 	*get_value_str(char *str)
{
	int		len;
	char 	*value_str;
	int 	i;

	len = 0;
	while (str[len] && str[len] != ' ' && !is_shield(&str[len]) && str[len] != '\\')
		len++;
	if (!(value_str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		value_str[i] = str[i];
		i++;
	}
	value_str[i] = '\0';
	return (value_str);
}

BOOL is_masked(char *str, char shield_char)
{
	if (*str =='\\' && *(str + 1) == '$')
		return (TRUE);
	if (shield_char != '\'' && *str == '\\' && *(str + 1) == '\\')
		return (TRUE);
	if (shield_char != '\'' && *str == '\\' && *(str + 1) == '"')
		return (TRUE);
	if (shield_char != '\"' && *str == '\\' && *(str + 1) == '\'')
		return (TRUE);
	return (FALSE);
}

BOOL 	change_shield_char_value(char *shield_char, char *str)
{
	if (*str == '\'' || *str == '"')
	{
		*shield_char = *str;
		return (TRUE);
	}
	else if (*shield_char != 0 && (*str == '\'' || *str == '"'))
	{
		*shield_char = 0;
		return (TRUE);
	}
	return (FALSE);
}

int		get_parsed_arg_len (char *str, t_env *env)
{
	char 	*value_str;
	char 	*env_value;
	char	shield_char;
	int		len;

	shield_char = 0;
	if (!str)
		return (ERROR);
	len = 0;
	while (*str)
	{
		if (change_shield_char_value(&shield_char, str))
			str++;
		else if (is_masked(str, shield_char))
		{
			len++;
			str += 2;
		}
		else if (*str == '$' && shield_char != '\'')
		{
			if (!(value_str = get_value_str(++str)))
				return (ERROR);
			if ((env_value = get_env_value(value_str, &env)))
				len += ft_strlen(env_value);
			str += ft_strlen(value_str);
			free(value_str);
			value_str = NULL;
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

char	*get_parsed_arg(char *str, t_env *env)
{
	char	shield_char;
	char 	*value_str;
	char	*env_value;
	char 	*ret_str;
	int		len;
	int		i;

	if ((len = get_parsed_arg_len(str, env)) == ERROR)
		return (NULL);
	if (!(ret_str = ft_calloc(sizeof(char), len + 1)))
		return (NULL);
	i = 0;
	shield_char = 0;
	while (i < len)
	{
		if (change_shield_char_value(&shield_char, str))
			str++;
		else if (is_masked(str, shield_char))
		{
			ret_str[i++] = *(str + 1);
			str += 2;
		}
		else if (*str == '$' && shield_char != '\'')
		{
			if (!(value_str = get_value_str(++str)))
			{
				free(ret_str);
				return (NULL);
			}
			if ((env_value = get_env_value(value_str, &env)))
			{
				ft_strlcat(ret_str, env_value, len + 1);
				i += ft_strlen(env_value);
			}
			str += ft_strlen(value_str);
			free(value_str);
			value_str = NULL;
		}
		else
			ret_str[i++] = *str++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}

char	**get_arguments(char *str, t_env *env)
{
	char	**t_args;
	char	**args;
	int 	i;

	if (!(t_args = advanced_split(str, is_redirect_and_space, 0)))
		return (NULL);
	if (!(args = (char **)malloc(sizeof(char *) * str_arr_len(t_args) + 1)))
		return (NULL);
	i = 0;
	while (t_args[i])
	{
		if (!(args[i] = get_parsed_arg(t_args[i], env)))
		{
			free_str_arr(&t_args);
			free_str_arr(&args);
			return (NULL);
		}
		i++;
	}
	args[i] = NULL;
	free_str_arr(&t_args);
	return (args);
}

int 	skip_words(char *str)
{
	int		cnt;

	cnt = 0;
	while (str[cnt] && str[cnt] != ' ')
		cnt++;
	return (cnt);
}

int parse_command(char *str, t_command *command, t_env *env)
{
	char	**t_args;
	BOOL	redirect_flag;
	int 	status;

	while (*str && ft_isspace(*str))
		str++;
	if (!(command->str = ft_strdup(str)))
		return (ERROR);
	if (!(t_args = get_arguments(str, env)))
		return (ERROR);
	status = TRUE;
	while (status == TRUE && *t_args)
	{
		redirect_flag = skip_delimiters(&str);
		if (redirect_flag == TRUE)
			status = str_arr_append(&command->files, *t_args);
		else
			status = str_arr_append(&command->args, *t_args);
		str += skip_words(str);
		t_args++;
	}
	return (status == TRUE ? TRUE : ERROR);
}
