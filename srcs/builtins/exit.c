/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:35:31 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/05 18:33:05 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	·		get_number(char *str)¬
{¬
	long long int	out;¬
	int	·		sign;¬
¬
	out = 0;¬
	sign = 1;¬
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')¬
	{¬
		if (*str == '-')¬
			sign = -1;¬
		++str;¬
	}¬
	while ((*str >= '0') && (*str <= '9'))¬
	{¬
		out = 10 * out + (*str - '0');¬
		++str;¬
	}¬
	while (*str == ' ' || *str == '\t')
		str++;
	return (sign * out);¬
}¬

static int	·		check_number(char *str)¬
{¬
	long long int	out;¬
	int	·		sign;¬
¬
	out = 0;¬
	sign = 1;¬
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')¬
	{¬
		if (*str == '-')¬
			sign = -1;¬
		++str;¬
	}¬
	if ((*str < '0') || (*str >= '9'))
		return (0);
	while ((*str >= '0') && (*str <= '9'))¬
	{¬
		if (out > 922337203685477580 && *str > '7'¬
				&& *str <= '9' && sign == 1)¬
			return (0);¬
		if (out > 922337203685477580 && *str == '9' && sign == -1)¬
			return (0);¬
		out = 10 * out + (*str - '0');¬
		++str;¬
	}¬
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str != '\0')
		return (0);
	return (1);¬
}¬

int	ft_exit(char **argv, int *flag)
{
	unsigned char	out;

	ft_putstr_fd("exit\n", 1);
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
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	else
		out = (unsigned char)get_number;
	*flag = 1;
	return((int)out);
}
