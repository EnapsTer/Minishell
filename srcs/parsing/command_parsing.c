/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:42:43 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/04 20:26:42 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "advanced_split.h"
#include "environment_utils.h"
#include "start.h"
#include "delimiter_comparators.h"
#include "strs_utils.h"

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
	str++;
	while (*str && *str != ' ')
		len++;
	if (!(value_str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		value_str[i] = str[i];
		i++;
	}
	value_str[i] = '\0';
	return (value_str);
}

int		get_parsed_str_len (char *str, t_env *env)
{
	char 	*value_str;
	char 	*env_value;
	char	shield_char;
	int		len;

	shield_char = 0;
	if (!str)
		return (ERROR);
	if (str[0] == '\'' || str[0] == '"')
	{
		shield_char = str[0];
		str++;
	}
	len = 0;
	while (*str && *str != shield_char)
	{
		if (*str == '$')
		{
			value_str = get_value_str(str);
			if (!(env_value = get_env_value(value_str, &env)))
			{
				while (*str && *str != ' ')
					str++;
			}
			else
			{
				if (shield_char == '"')
					len += ft_strlen(env_value);
			}
			if (value_str)
			{
				free(value_str);
				value_str = NULL;
			}
		}

		str++;
	}


}

char	*get_parsed_str(char *str, t_env *env)
{
	char	shield_char;
	char 	*value_str;
	char	*env_value;
	char 	*ret_str;
	int		len;

	shield_char = 0;
	if (!str)
		return (NULL);
	if (str[0] == '\'' || str[0] == '"')
	{
		shield_char = str[0];
		str++;
	}
	while (*str && *str != shield_char)
	{
		if (*str == '$')
		{
			value_str = get_value_str(str);
			if (!(env_value = get_env_value(value_str, &env)))
			{
				while (*str && *str != ' ')
					str++;
			}
			else
			{
				if (shield_char == '"')
					ret_str = superstrjoin(ret_str, env_value);
			}
			if (value_str)
			{
				free(value_str);
				value_str = NULL;
			}
		}

		str++;
	}

}

char	**get_arguments(char *str, t_env *env)
{
	char	**t_args;
	char	**args;
	int 	i;

	if (!(t_args = advanced_split(str, is_redirect_and_space, 0)))
		return (NULL);
	if (!(args = (char **)malloc(sizeof(char *) * str_arr_len(t_args))))
		return (NULL);
	i = 0;
	while (*t_args)
	{
		args[i] = get_parsed_str(t_args[i], env);
		t_args++;
	}
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
	// здесь продумать логику с подставлениями переменных
	t_args = advanced_split(str, is_redirect_and_space, 1);
	if (!(t_args))
		return (ERROR);
	status = TRUE;
	while (status == TRUE && *t_args && **t_args)
	{
		redirect_flag = skip_delimiters(&str);
		if (redirect_flag == TRUE)
			status = str_arr_append(&command->files, *t_args);
		else
			status = str_arr_append(&command->args, *t_args);
		str += is_shield(str) ? ft_strlen(*t_args) + 2 : ft_strlen(*t_args);
		t_args++;
	}
	return (status == TRUE ? TRUE : ERROR);
}
