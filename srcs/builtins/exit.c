/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:35:31 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/19 17:48:18 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "start.h"

void		ft_skip_spaces(char **str)
{
	if (str && *str)
	{
		while (**str == ' ' || **str == '\t')
			*str = *str + 1;
	}
}

static void	handle_sign(char **str, int *sign)
{
	if (str && *str)
	{
		if (**str == '-' || **str == '+')
		{
			if (**str == '-')
				*sign = -1;
			*str = *str + 1;
		}
	}
}

static int	get_number(char *str)
{
	long int	out;
	int			sign;

	out = 0;
	sign = 1;
	ft_skip_spaces(&str);
	handle_sign(&str, &sign);
	while ((*str >= '0') && (*str <= '9'))
	{
		out = 10 * out + (*str - '0');
		str++;
	}
	ft_skip_spaces(&str);
	return (sign * out);
}

static int	check_number(char *str)
{
	long int	out;
	int			sign;

	out = 0;
	sign = 1;
	ft_skip_spaces(&str);
	handle_sign(&str, &sign);
	if ((*str < '0') || (*str > '9'))
		return (0);
	while ((*str >= '0') && (*str <= '9'))
	{
		if (sign == 1 && ft_isdigit(*str) && ((out >= 922337203685477580
								&& *str > '7') || out > 922337203685477580))
			return (0);
		if (sign == -1 && ft_isdigit(*str) && ((out >= 922337203685477580
								&& *str == '9') || out > 922337203685477580))
			return (0);
		out = 10 * out + (*str - '0');
		str++;
	}
	ft_skip_spaces(&str);
	if (*str != '\0')
		return (0);
	return (1);
}

int			ft_exit(char **argv)
{
	unsigned char out;

	if (!argv[1])
		out = 0;
	else if (!check_number(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		out = 255;
	}
	else if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
		out = (unsigned char)get_number(argv[1]);
	nullify_g_str();
	return ((int)out);
}
