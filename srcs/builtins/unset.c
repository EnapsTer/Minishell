/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:35:30 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/12 15:18:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start.h"
#include <libft.h>

int	unset(char **argv, t_env *env)
{
	int	count;
	int	out;

	count = 1;
	out = 0;
	while (argv[count])
		{
			if (!is_valid_env_name(argv[count]))
			{
				ft_putstr_fd("minishell: unset: `", 2);
				ft_putstr_fd(argv[count], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				out = 1;
				continue;
			}
			else
				delete_env_var(argv[count], env);
			count++;
		}
	return (out);
}
