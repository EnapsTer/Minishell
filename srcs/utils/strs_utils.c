/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:50:43 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 19:21:23 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"

int		ft_unregister_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else if (ft_isalpha(s1[i]) && ft_isalpha(s2[i]))
		{
			if (s1[i] == s2[i] - 32 || s1[i] - 32 == s2[i])
				i++;
			else
				break ;
		}
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

int		str_arr_len(char **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int		str_arr_append(char ***arr, char *line)
{
	char	**temp;
	int		i;

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

void	free_str_arr(char ***arr)
{
	int	i;

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
