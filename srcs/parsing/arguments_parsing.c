/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:30:46 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 18:51:52 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "start.h"
#include "libft.h"
#include "delimiter_comparators.h"
#include "strs_utils.h"
#include "advanced_split.h"
#include "arguments_parsing.h"

int		get_arg_value_len(char **str, t_env *env)
{
	char	*value_str;
	char	*env_value;
	int		len;

	len = 0;
	env_value = NULL;
	if (!(value_str = get_value_str(++(*str))))
		return (ERROR);
	if (!(*value_str))
		len++;
	else if ((env_value = get_env_value(value_str, &env)))
		len += ft_strlen(env_value);
	(*str) += ft_strlen(value_str);
	free(value_str);
	value_str = NULL;
	if (!env_value && len == 0)
		len++;
	return (len);
}

int		get_parsed_arg_len(char *str, t_env *env)
{
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
			len += get_arg_value_len(&str, env);
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

int		fill_str_with_env_value(t_arg_parse *arg_parse, char **str, t_env *env)
{
	char	*value_str;
	char	*env_value;

	if (!(value_str = get_value_str(++(*str))))
	{
		free(arg_parse->ret_str);
		return (ERROR);
	}
	if (!(*value_str))
		arg_parse->ret_str[arg_parse->i++] = *((*str) - 1);
	else if ((env_value = get_env_value(value_str, &env)))
	{
		ft_strlcat(arg_parse->ret_str, env_value, arg_parse->len + 1);
		arg_parse->i += ft_strlen(env_value);
	}
	else if (arg_parse->len == 1)
		arg_parse->ret_str[arg_parse->i++] = '\r';
	*str += ft_strlen(value_str);
	free(value_str);
	value_str = NULL;
	return (TRUE);
}

char	*get_parsed_arg(char *str, t_env *env)
{
	t_arg_parse	arg_parse;
	char		shield_char;

	if ((arg_parse.len = get_parsed_arg_len(str, env)) == ERROR ||
			!(arg_parse.ret_str = ft_calloc(sizeof(char), arg_parse.len + 1)))
		return (NULL);
	arg_parse.i = 0;
	shield_char = 0;
	while (arg_parse.i < arg_parse.len)
	{
		if (change_shield_char_value(&shield_char, str))
			str++;
		else if (is_masked(str, shield_char))
		{
			arg_parse.ret_str[arg_parse.i] = *(str + 1);
			str += 2;
		}
		else if (*str == '$' && shield_char != '\'')
			fill_str_with_env_value(&arg_parse, &str, env);
		else
			arg_parse.ret_str[arg_parse.i++] = *str++;
	}
	arg_parse.ret_str[arg_parse.i] = '\0';
	return (arg_parse.ret_str);
}

char	**get_arguments(char *str, t_env *env)
{
	char	**t_args;
	char	**args;
	int		i;

	if (!(t_args = advanced_split(str, is_redirect_and_space, 0)))
		return (NULL);
	if (!(args = (char **)malloc(sizeof(char *) * (str_arr_len(t_args) + 1))))
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
