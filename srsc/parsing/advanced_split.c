/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:39:39 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/26 17:42:15 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <advanced_split_utils.h>
#include <advanced_split_free_utils.h>

/*
** Returns strings splited by delimiter use shielding
*/

char	**advanced_split(char *str, char delimiter, int shielding)
{
	char	**strs;
	int		strs_count;

	if ((strs_count = count_strs(str, delimiter, shielding)) == ERROR)
		return (NULL);
	if (!(strs = malloc(sizeof(char *) * (strs_count + 1))))
		return (NULL);
	strs[strs_count] = NULL;
	if ((fill_strs(strs, str, delimiter, shielding)) == ERROR)
	{
		free_filled_strs(&strs);
		return (NULL);
	}
	return (strs);
}