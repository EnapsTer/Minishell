/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:09:07 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/26 18:12:53 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** Change value of shield char and return is changed or not
*/

BOOL change_shield_char (char *shield_char, char *str, char delim, int shield)
{
	if ((shield && !(*shield_char) && (*str == '\'' || *str == '"')))
		*shield_char = *str;
	else if (shield && *shield_char && *shield_char == *str)
		*shield_char = 0;
	else if (!shield && *(str + 1) == delim && !(*shield_char) &&
			 ((*str == '\'' || *str == '"')))
		*shield_char = *str;
	else if (!shield && *(str - 1) == delim && *shield_char
					&& *shield_char == *str)
		*shield_char = 0;
	else
		return (FALSE);
	return (TRUE);
}

/*
** Returns count of strings splited by delimiter use shielding
*/

int		count_strs(char *str, char delimiter, int shielding)
{
	int		count;
	char 	shield_char;

	count = 0;
	shield_char = 0;
	while (*str)
	{
		change_shield_char(&shield_char, str, delimiter, shielding);
		if (*str == delimiter && !shield_char)
			count++;
		str++;
	}
	return (shield_char ? ERROR : count + 1);
}

/*
** Returns len of shielded string
*/

int		get_str_len(char *str, char delimiter, int shielding)
{
	int len;
	char 	shield_char;

	shield_char = 0;
	len = 0;
	while (*str)
	{
		if (!change_shield_char(&shield_char, str, delimiter, shielding))
			len++;
		if (*str++ == delimiter && !shield_char)
			break;
	}
	return (len);
}


/*
** Returns filled string proceeding from delimiter and shielding
*/

char	*get_filled_str(char **str, char delimiter, int shielding)
{
	int		i;
	int		len;
	char 	shield_char;
	char 	*result;

	i = 0;
	len = get_str_len(*str, delimiter, shielding);
	shield_char = 0;
	if (!(result = malloc(sizeof(char) * len)))
		return (NULL);
	while (**str && (**str != delimiter || shield_char))
	{
		if (!change_shield_char(&shield_char, *str, delimiter, shielding))
			result[i++] = **str;
		(*str)++;
	}
	result[i] = '\0';
	if (**str == delimiter)
		(*str)++;
	return (result);
}

/*
** Fill strs proceeding from delimiter and shielding
*/

int		fill_strs(char **strs, char *str, char delimiter, int shielding)
{
	int i;
	int len;

	i = 0;
	if ((len = count_strs(str, delimiter, shielding)) == ERROR)
		return (ERROR);
	while (i < len)
	{
		if (!(strs[i] = get_filled_str(&str, delimiter, shielding)))
			return (ERROR);
		i++;
	}
	return (TRUE);
}
