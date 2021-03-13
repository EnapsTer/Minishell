/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:40:17 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/13 11:18:11 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <libft.h>

int	pwd(void)
{
	char	*buf;

	if (!(buf = getcwd(NULL, 0)))
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
	return (0);
}