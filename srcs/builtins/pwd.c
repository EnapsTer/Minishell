/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:40:17 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/03 16:56:38 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <libft.h>

int	pwd(void)
{
	char	*buf;

	buf = NULL;
	if (!getcwd(buf, 0))
	{
		ft_putstr_fd("pwd:", 2);
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
	exit(0);
}
