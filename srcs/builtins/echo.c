/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:08:30 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/12 15:18:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	echo(char **argv)
{
	int	flag_n;
	int	count;

	count = 1;
	flag_n = 0;
	while (argv[count])
	{
		if (!ft_strcmp(argv[count], "-n"))
			flag_n++;
		count++;
	}
	count = 1;
	while (argv[count + flag_n])
	{
		if (count > 1)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(argv[count + flag_n], 1);
		count++;
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
	return (0);
}
