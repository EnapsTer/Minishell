/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_comparators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:28:59 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/31 15:41:14 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_semicolon(char *str)
{
	if (*str == ';')
		return (1);
	return (FALSE);
}

int 	is_shield(char *str)
{
	return (*str == '\'' || *str == '"');
}

int 	is_pipe(char *str)
{
	if (*str == '|')
		return (1);
	return (FALSE);
}

int		is_redirect(char *str)
{
	if (*str == '>' && *(str + 1) == '>')
		return (2);
	else if (*str == '>')
		return (1);
	else if (*str == '<')
		return (1);
	return (FALSE);
}

int 	is_redirect_and_space(char *str)
{
	return (is_redirect(str) || *str == ' ');
}