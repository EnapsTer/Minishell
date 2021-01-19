/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:16:36 by aherlind          #+#    #+#             */
/*   Updated: 2020/11/04 13:16:39 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	n;

	n = ft_strlen(s);
	if (c == 0)
		return ((char *)&s[n]);
	while (n > 0)
	{
		if (s[n - 1] == (char)c)
			return ((char *)&s[n - 1]);
		n--;
	}
	return (NULL);
}
