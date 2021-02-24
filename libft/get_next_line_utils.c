/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:23:47 by aherlind          #+#    #+#             */
/*   Updated: 2020/11/10 16:23:52 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(char *s)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_gnl_strdup(char *s1)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	len;
	size_t	i;
	char	*tmp;

	tmp = s1;
	i = 0;
	len = ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	while (s1 && *s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	if (tmp)
		free(tmp);
	return (result);
}

int		index_of_char(char *s, char c)
{
	int index;

	index = -1;
	while (s[++index])
		if (s[index] == c)
			return (index);
	return (-1);
}
