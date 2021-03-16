/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quoted_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:59:10 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/16 17:56:57 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "start.h"
#include <libft.h>

static void	handle_single_quote(int *quote_flag, int *strlen, char **out)
{
	if (*quote_flag == 1 && *quote_flag != 2)
		*quote_flag = 0;
	else if (*quote_flag != 2)
	{
		if (out)
			(*out)[*strlen] = '\r';
		*strlen = *strlen + 1;
		*quote_flag = 1;
	}
}

static void	handle_double_quote(int *quote_flag, int *strlen, char **out)
{
	if (*quote_flag == 2 && *quote_flag != 1)
		*quote_flag = 0;
	else if (*quote_flag != 1)
	{
		if (out)
			(*out)[*strlen] = '\r';
		*strlen = *strlen + 1;
		*quote_flag = 2;
	}
}

static void	get_final_str(char *str, char **out)
{
	int	i;
	int	strlen;
	int	quote_flag;

	i = 0;
	strlen = 0;
	quote_flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (quote_flag == 1 || !is_mirrored(str, i)))
			handle_single_quote(&quote_flag, &strlen, out);
		else if (str[i] == '"' && !is_mirrored(str, i))
			handle_double_quote(&quote_flag, &strlen, out);
		else if (quote_flag > 0)
			;
		else
			(*out)[strlen++] = str[i];
		i++;
	}
	(*out)[strlen] = '\0';
}

static int	get_final_strlen(char *str)
{
	int	i;
	int	strlen;
	int	quote_flag;

	i = 0;
	strlen = 0;
	quote_flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (quote_flag == 1 || !is_mirrored(str, i)))
			handle_single_quote(&quote_flag, &strlen, NULL);
		else if (str[i] == '"' && !is_mirrored(str, i))
			handle_double_quote(&quote_flag, &strlen, NULL);
		else if (quote_flag > 0)
			;
		else
			strlen++;
		i++;
	}
	if (quote_flag > 0)
		return (-1);
	return (strlen);
}

char		*remove_quoted_str(char *str, t_env **env, int *continue_flag)
{
	char	*out;
	int		strlen;

	if (!str || str[0] == '\0')
	{
		out = ft_strdup("");
		return (out);
	}
	strlen = get_final_strlen(str);
	if (strlen == -1)
	{
		print_syntax_error("open quotes", env, continue_flag);
		return (NULL);
	}
	if (!(out = (char*)malloc(sizeof(char) * (strlen + 1))))
	{
		*continue_flag = MALLOC_ERROR;
		return (NULL);
	}
	get_final_str(str, &out);
	return (out);
}
