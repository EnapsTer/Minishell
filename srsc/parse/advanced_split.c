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
		if (shielding && !shield_char && (*str == '\'' || *str == '"'))
			shield_char = *str;
		else if (shielding && shield_char && shield_char == *str)
			shield_char = 0;
		else
			len++;
		if (*str++ == delimiter && !shield_char)
			break;
	}
	return (len);
}

/*
** Fill strs proceeding from delimiter and shielding
*/

//подогнать 26 строк
int		fill_strs(char **strs, char *str, char delimiter, int shielding)
{
	int 	len;
	int 	i;
	char 	shield_char;

	shield_char = 0;
	while (*strs)
	{
		i = 0;
		len = get_str_len(str, delimiter, shielding);
		if (!(*strs = malloc(sizeof(char) * len)))
			return (ERROR);
		while (*str && (*str != delimiter || shield_char))
		{
			if (shielding && !shield_char && (*str == '\'' || *str == '"'))
				shield_char = *str;
			else if (shielding && shield_char && shield_char == *str)
				shield_char = 0;
			else
				(*strs)[i++] = *str;
			str++;
		}
		(*strs)[i] = '\0';
		if (*str == delimiter)
			str++;
		strs++;
	}
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
		if (shielding && !shield_char && (*str == '\'' || *str == '"'))
			shield_char = *str;
		else if (shielding && shield_char && shield_char == *str)
			shield_char = 0;
		if (*str == delimiter && !shield_char)
			count++;
		str++;
	}
	return (shield_char ? ERROR : count + 1);
}

/*
** Returns strings splited by delimiter use shielding
*/

char	**advanced_split(char *str, char delimiter, int shielding)
{
	char	**strs;
	int		strs_count;

	strs_count = count_strs(str, delimiter, shielding);
	if (!(strs = malloc(sizeof(char *) * (strs_count + 1))))
		return (NULL);
	strs[strs_count] = NULL;
	if ((fill_strs(strs, str, delimiter, shielding)) == ERROR)
		return (NULL);

}