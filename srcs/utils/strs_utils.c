/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:50:43 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/01 13:02:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		str_arr_len(char **arr)
{
	int     len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int             str_arr_append(char ***arr, char *line)
{
	char    **temp;
	int             i;

	i = -1;
	if (!(temp = (char **)malloc(sizeof(char *) * (str_arr_len(*arr) + 2))))
		return (ERROR);
	if (!(*arr))
		temp[++i] = line;
	else
	{
		while ((*arr)[++i])
			temp[i] = (*arr)[i];
		temp[i] = line;
		free(*arr);
	}
	temp[++i] = NULL;
	*arr = temp;
	return (TRUE);
}


void    free_str_arr(char ***arr)
{
	int     i;

	i = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
