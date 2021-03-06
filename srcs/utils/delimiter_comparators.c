/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_comparators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:28:59 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 19:17:57 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_semicolon(char *str)
{
	if (*str == ';')
		return (1);
	return (FALSE);
}

int		is_shield(char *str)
{
	return (*str == '\'' || *str == '"');
}

int		is_pipe(char *str)
{
	if (*str == '|')
		return (1);
	return (FALSE);
}

int		is_equal(char *str)
{
	return (*str == '=');
}

int		is_colon(char *str)
{
	return (*str == ':');
}
