/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:39:39 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/19 14:39:40 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "advanced_split.h"
#include <stdlib.h>
#include <stdio.h>

/*
** Change value of shield char and return is changed or not
*/

BOOL change_shield_char(char *shield_char, char c, int shielding)
{
	if (shielding && !(*shield_char) && (c == '\'' || c == '"'))
	{
		*shield_char = c;
		return (TRUE);
	}
	else if (shielding && *shield_char && *shield_char == c)
	{
		*shield_char = 0;
		return (TRUE);
	}
	return (FALSE);
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
		if (!change_shield_char(&shield_char, *str, shielding))
			len++;
		if (*str++ == delimiter && !shield_char)
			break;
	}
	return (len);
}

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
		if (!change_shield_char(&shield_char, **str, shielding))
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
		change_shield_char(&shield_char, *str, shielding);
		if (*str == delimiter && !shield_char)
			count++;
		str++;
	}
	return (shield_char ? ERROR : count + 1);
}

int		fill_strs(char **strs, char *str, char delimiter, int shielding)
{
	int i;
	int len;

	i = 0;
	len = count_strs(str, delimiter, shielding);
	while (i < len)
	{
		strs[i] = get_filled_str(&str, delimiter, shielding);
		i++;
	}
	return (TRUE);
}

/*
** Returns strings splited by delimiter use shielding
*/

//иногда не записывает
char	**advanced_split(char *str, char delimiter, int shielding)
{
	char	**strs;
	int		strs_count;

	strs_count = count_strs(str, delimiter, shielding);
	if (!(strs = malloc(sizeof(char *) * (strs_count + 1))))
		return (NULL);
	strs[strs_count] = NULL;
	if ((fill_strs(strs, str, delimiter, shielding)) == ERROR)
	{
		printf("error");
		return (NULL);
	}
	return (strs);
}