/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:04:46 by aherlind          #+#    #+#             */
/*   Updated: 2020/11/04 13:04:48 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			get_num_len(long int c)
{
	size_t	len;

	len = 0;
	while (c / 10)
	{
		c /= 10;
		len++;
	}
	return (c < 0 ? len + 2 : len + 1);
}

char			*ft_itoa(long int n)
{
	unsigned int	num;
	long int		len;
	char			*s;
	unsigned int	i;

	num = n < 0 ? n * -1 : n;
	i = 0;
	len = get_num_len(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (n < 0)
		s[i++] = '-';
	s[len--] = '\0';
	while (len >= i)
	{
		s[len] = num % 10 + '0';
		num /= 10;
		len--;
	}
	return (s);
}
