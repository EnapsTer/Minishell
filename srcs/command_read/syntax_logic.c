/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:37:11 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/11 15:14:40 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start.h"
#include <libft.h>

int	is_piped_syntax_correct(char *str)
{
	int	count;

	count = 0;
	if (only_spaces_after(str, -1))
			return (0);
	while (str[count])
	{
		if ((str[count] == '>' || str[count] == '<')
					&& !(is_mirrored(str, count)) &&
					only_spaces_after(str, count))
		return (0);
		count++;
	}
	return (1);
}

int	is_string_error(char *str, t_env **env, int *continue_flag)
{
	if (!str)
		return (0);
	else if (ft_strnstr(str, ";;", ministrlen(str)))
			print_syntax_error("token `;;'", env, continue_flag);
	else if (ft_strnstr(str, "||", ministrlen(str)))
			print_syntax_error("token `||'", env, continue_flag);
	else if (ft_strnstr(str, ">|", ministrlen(str)))
			print_syntax_error("token `|'", env, continue_flag);
	else if (ft_strnstr(str, ">>>", ministrlen(str)))
			print_syntax_error("token `>'", env, continue_flag);
	else if (ft_strnstr(str, "<<", ministrlen(str)))
			print_syntax_error("token `<'", env, continue_flag);
	else if (ft_strnstr(str, "><", ministrlen(str)))
			print_syntax_error("token `<'", env, continue_flag);
	else if (str[0] == ';')
			print_syntax_error("token `;'", env, continue_flag);
	else if (str[0] == '|')
			print_syntax_error("token `|'", env, continue_flag);
	else
		return (0);
	return (1);
}

int	is_semicoloned_syntax_correct(char *str)
{
	int	count;

	count = 0;
	if (only_spaces_after(str, -1))
			return (0);
	while (str[count])
	{
		if ((str[count] == '>' || str[count] == '<'|| str[count] == '|')
					&& !(is_mirrored(str, count)) &&
					only_spaces_after(str, count))
		return (0);
		count++;
	}
	return (1);
}

