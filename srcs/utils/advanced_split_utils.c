/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:09:07 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/03 17:32:39 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** Change value of shield char and return is changed or not
*/

BOOL change_shield_char (char *shield_char, char *str,
						 int (*is_delimiter)(char *), int shield)
{
	if (!(*shield_char) && (*str == '\'' || *str == '"'))
	{
		*shield_char = *str;
		return (shield == 1 ? TRUE : FALSE);
	}
	else if (*shield_char && *shield_char == *str)
	{
		*shield_char = 0;
		return (shield == 1 ? TRUE : FALSE);
	}
//	else if (!shield && is_delimiter(str) && shield_char)
//		return (FALSE);
//	else if (!shield && is_delimiter(str + 1) && !(*shield_char) &&
//			 ((*str == '\'' || *str == '"')))
//		*shield_char = *str;
//	else if (!shield && is_delimiter(str - 1) && *shield_char
//			 && *shield_char == *str)
//		*shield_char = 0;
	else
		return (FALSE);
	return (TRUE);
}

/*
** Returns count of strings splited by is_delimiter use shielding
*/

int		count_strs(char *str, int (*is_delimiter)(char *), int shielding)
{
	int		count;
	char 	shield_char;

	count = 0;
	shield_char = 0;
	while (is_delimiter(str))
		str += is_delimiter(str);
	while (*str)
	{
		change_shield_char(&shield_char, str, is_delimiter, shielding);
		if (is_delimiter(str) && !shield_char)
		{
			while (is_delimiter(str))
				str += is_delimiter(str);
			if (*str)
				count++;
		}
		else
			str++;
	}
	return (shield_char ? ERROR : count + 1);
}

/*
** Returns len of shielded string
*/

int		get_str_len(char *str, int (*is_delimiter)(char *), int shielding)
{
	int len;
	char 	shield_char;

	shield_char = 0;
	len = 0;
	while (*str)
	{
		if (!change_shield_char(&shield_char, str, is_delimiter, shielding))
			len++;
		if (is_delimiter(str++) && !shield_char)
			break;
	}
	return (len);
}


/*
** Returns filled string proceeding from is_delimiter and shielding
*/

char	*get_filled_str(char **str, int (*is_delimiter)(char *), int shielding)
{
	int		i;
	int		len;
	char 	shield_char;
	char 	*result;

	i = 0;
	while (is_delimiter(*str))
		*str += is_delimiter(*str);
	len = get_str_len(*str, is_delimiter, shielding);
	shield_char = 0;
	if (!(result = malloc(sizeof(char) * (len)))) // возможно нужно len + 1
		return (NULL);
	while (**str && (!is_delimiter(*str) || shield_char))
	{
		if (!change_shield_char(&shield_char, *str, is_delimiter, shielding))
			result[i++] = **str;
		(*str)++;
	}
	result[i] = '\0';
	while (is_delimiter(*str))
		*str += is_delimiter(*str);
	return (result);
}

/*
** Fill strs proceeding from is_delimiter and shielding
*/

int		fill_strs(char **strs, char *str,
			   int (*is_delimiter)(char *) , int shielding)
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
