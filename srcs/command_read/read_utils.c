/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:42:33 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/12 15:18:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "start.h"

int	ministrlen(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return(0);
	while (*str++)
		count++;
	return (count);
}

void	strzero(char *str)
{
	while (*str)
	{
		*str = '\0';
		str++;
	}
}

char	*superstrjoin(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	i;
	char	*cs1;

	cs1 = s1;
	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	i = 0;
	result = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1 && *s1)
		result[i++] = *s1++;
	while (s2 && *s2)
		result[i++] = *s2++;
	result[i] = '\0';
	if (cs1)
		free(cs1);
	return (result);
}

