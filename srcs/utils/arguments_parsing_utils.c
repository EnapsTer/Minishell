/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parsing_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:24:12 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/12 15:18:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "delimiter_comparators.h"

int 	skip_words(char *str)
{
	int		cnt;

	cnt = 0;
	while (str[cnt] && str[cnt] != ' ')
		cnt++;
	return (cnt);
}

BOOL	is_valid_env_name_char(char c)
{
	if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
		return (TRUE);
	return (FALSE);
}

char 	*get_value_str(char *str)
{
	int		len;
	char 	*value_str;
	int 	i;

	len = 0;
	if (str[len] == '?')
		len++;
	else
		while (str[len] && is_valid_env_name_char(str[len]))
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
	if (shield_char != '\'' && *str =='\\' && *(str + 1) == '$')
		return (TRUE);
	if (shield_char != '\'' && *str == '\\' && *(str + 1) == '\\')
		return (TRUE);
	if (shield_char != '\'' && *str == '\\' && *(str + 1) == '"')
		return (TRUE);
	return (FALSE);
}

BOOL 	change_shield_char_value(char *shield_char, char *str)
{
	if (*shield_char == 0 && is_shield(str))
	{
		*shield_char = *str;
		return (TRUE);
	}
	else if (*shield_char != 0 && *str == *shield_char)
	{
		*shield_char = 0;
		return (TRUE);
	}
	return (FALSE);
}