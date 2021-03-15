/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_delimiter_comparators.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:17:38 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 19:17:57 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		is_redirect_and_space(char *str)
{
	return (is_redirect(str) || *str == ' ');
}
