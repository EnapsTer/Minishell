/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:09:07 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/12 15:18:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "start.h"
#include "delimiter_comparators.h"
#include <stdlib.h>

/*
** Change value of shield char and return is changed or not
*/

BOOL	change_shield_char(char *shield_char, char *str, int i, int shield)
{
	if (!(*shield_char) && is_shield(str + i) && !is_mirrored(str, i))
	{
		*shield_char = *(str + i);
		return (shield == 1 ? TRUE : FALSE);
	}
	else if (*shield_char && !is_mirrored(str, i) && *shield_char == *(str + i))
	{
		*shield_char = 0;
		return (shield == 1 ? TRUE : FALSE);
	}
	else
		return (FALSE);
}

/*
** Returns count of strings splited by is_delimiter use shielding
*/

int		count_strs(char *str, int (*is_delimiter)(char *), int shielding)
{
	int		count;
	char	shield_char;
	int		i;

	count = 0;
	shield_char = 0;
	i = 0;
	while (is_delimiter(str + i))
		i += is_delimiter(str);
	while (str[i])
	{
		change_shield_char(&shield_char, str, i, shielding);
		if (is_delimiter(str + i) && !shield_char)
		{
			while (is_delimiter(str + i))
				i += is_delimiter(str + i);
			if (str[i])
				count++;
		}
		else
			i++;
	}
	return (shield_char ? ERROR : count + 1);
}

/*
** Returns len of shielded string
*/

int		get_str_len(char *str, int (*is_delimiter)(char *), int shielding)
{
	int		len;
	char	shield_char;
	int		i;

	shield_char = 0;
	len = 0;
	i = 0;
	while (str[i])
	{
		if (!change_shield_char(&shield_char, str, i, shielding))
			len++;
		if (is_delimiter(str + i++) && !shield_char)
			break ;
	}
	return (len);
}

/*
** Returns filled string proceeding from is_delimiter and shielding
*/

char	*get_filled_str(char **str, int (*is_delimiter)(char *), int shielding)
{
	int		i;
	int		j;
	int		len;
	char	shield_char;
	char	*result;

	while (is_delimiter(*str))
		*str += is_delimiter(*str);
	len = get_str_len(*str, is_delimiter, shielding);
	shield_char = 0;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while ((*str)[j] && (!is_delimiter(*str + j) || shield_char))
	{
		if (!change_shield_char(&shield_char, *str, j, shielding))
			result[i++] = (*str)[j++];
	}
	result[i] = '\0';
	while (is_delimiter(*str + j))
		j += is_delimiter(*str + j);
	*str += j;
	return (result);
}

/*
** Fill strs proceeding from is_delimiter and shielding
*/

int		fill_strs(char **strs, char *str,
				int (*is_delimiter)(char *), int shielding)
{
	int i;
	int len;

	i = 0;
	if ((len = count_strs(str, is_delimiter, shielding)) == ERROR)
		return (ERROR);
	while (i < len)
	{
		if (!(strs[i] = get_filled_str(&str, is_delimiter, shielding)))
			return (ERROR);
		i++;
	}
	return (TRUE);
}
