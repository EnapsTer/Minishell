/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:42:43 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/04 12:16:20 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "advanced_split.h"
#include "delimiter_comparators.h"
#include <stdlib.h>
#include "strs_utils.h"
#include "commands.h"

int 		skip_delimiters(char **str)
{
	BOOL	redirect_flag;

	redirect_flag = FALSE;
	while (**str && is_redirect_and_space(*str))
	{
		if (is_redirect(*str))
			redirect_flag = TRUE;
		(*str)++;
	}
	return (redirect_flag);
}

int 		parse_command(char *str, t_command *command)
{
	char	**t_args;
	BOOL	redirect_flag;

	while (*str && ft_isspace(*str))
		str++;
	t_args = advanced_split(str, is_redirect_and_space, 1);
	if (!(t_args))
		return (ERROR);
	command->name = *t_args++;
	str += ft_strlen(command->name);
	while (*t_args && **t_args)
	{
		redirect_flag = skip_delimiters(&str);
		if (redirect_flag == TRUE)
			str_arr_append(&command->files, *t_args);
		else
			str_arr_append(&command->args, *t_args);
		str += is_shield(str) ? ft_strlen(*t_args) + 2 : ft_strlen(*t_args);
		*t_args++;
	}
	return (TRUE);
}
