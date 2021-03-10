/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:42:43 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/10 16:37:14 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "start.h"
#include "arguments_parsing.h"
#include "delimiter_comparators.h"
#include "strs_utils.h"

#include <stdio.h>

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

int parse_command(char *str, t_command *command, t_env *env)
{
	char	**t_args;
	BOOL	redirect_flag;
	int 	status;
	int 	i;

	while (*str && ft_isspace(*str))
		str++;
	if (!(command->str = ft_strdup(str)))
		return (ERROR);
	if (!(t_args = get_arguments(str, env)))
		return (ERROR);
	status = TRUE;
	i = 0;
	while (status == TRUE && t_args[i])
	{
		redirect_flag = skip_delimiters(&str);
		if (t_args[i][0] != '\r' || t_args[i][1] != '\0')
		{
			if (redirect_flag == TRUE)
				status = str_arr_append(&command->files, ft_strdup(t_args[i]));
			else
				status = str_arr_append(&command->args, ft_strdup(t_args[i]));
		}
		str += skip_words(str);
		i++;
	}
	free_str_arr(&t_args);
	return (status == TRUE ? TRUE : ERROR);
}
