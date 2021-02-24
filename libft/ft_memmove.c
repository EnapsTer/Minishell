/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:09:33 by aherlind          #+#    #+#             */
/*   Updated: 2020/11/04 13:09:36 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			i;

	if (!len || dst == src)
		return (dst);
	dest = (unsigned char*)dst;
	source = (unsigned char*)src;
	i = 0;
	if (source < dest)
	{
		i = len;
		while (i > 0)
		{
			dest[i - 1] = source[i - 1];
			i--;
		}
	}
	else
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	return (dst);
}
