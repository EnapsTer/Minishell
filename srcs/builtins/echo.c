/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:08:30 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/02 20:39:11 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	echo(char **argv)
{
	int	flag_n;
	int	count;

	count = 1;
	flag_n = 0;
	while (argv[count] && !ft_strcmp(argv[count], "-n"))
	{
		count++;
		flag_n++;
	}
	while (argv[count])
	{
		if (count > 1 + flag_n)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(argv[count + flag_n], 1);
		count++;
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
	exit (0);
}
