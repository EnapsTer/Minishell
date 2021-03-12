/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:32:27 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/12 15:18:05 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void 	print_error(char *command, char *message)
{
	if (command)
	{
		ft_putstr_fd("minishell: ", STDERROR);
		ft_putstr_fd(command, STDERROR);
		ft_putstr_fd(": ", STDERROR);
		ft_putstr_fd(message, STDERROR);
		ft_putstr_fd("\n", STDERROR);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERROR);
		ft_putstr_fd(message, STDERROR);
		ft_putstr_fd("\n", STDERROR);
	}
}

void 	print_error_with_exit(char *command, char *message, int exit_code)
{
	print_error(command, message);
	exit(exit_code);
}