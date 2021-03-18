/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:08:30 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/18 18:36:06 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	is_echo_n_flag(char *str)
{
	if (!str || *str != '-')
		return (0);
	*str = *str + 1;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		*str = *str + 1;
	}
	return (1);
}

int			echo(char **argv)
{
	int	flag_n;
	int	count;

	count = 1;
	flag_n = 0;
	while (argv[count])
	{
		if (is_echo_n_flag(argv[count]))
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
