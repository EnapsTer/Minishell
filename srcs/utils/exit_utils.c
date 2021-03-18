/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:37:35 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 12:40:59 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "start.h"
#include "libft.h"

void	handle_exit(int commands_len)
{
	if (!g_input_str && commands_len == 1)
		ft_putstr_fd("exit\n", STDIN);
}
