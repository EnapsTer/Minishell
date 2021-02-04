/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:39:39 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/31 15:35:16 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include "strs_utils.h"
#include <advanced_split_utils.h>

/*
** Returns strings splited by delimiter use shielding
*/

char	**advanced_split(char *str, int (*is_delimiter)(char *), int shielding)
{
	char	**strs;
	int		strs_count;

	if (*str == '\0')
		strs_count = 0;
	else if ((strs_count = count_strs(str, is_delimiter, shielding)) == ERROR)
		return (NULL);
	if (!(strs = malloc(sizeof(char *) * (strs_count + 1))))
		return (NULL);
	strs[strs_count] = NULL;
	if ((fill_strs(strs, str, is_delimiter, shielding)) == ERROR)
	{
		free_str_arr(&strs);
		return (NULL);
	}
	return (strs);
}