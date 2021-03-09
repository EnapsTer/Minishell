/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_new_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:27:49 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/09 15:46:37 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "start.h"
#include "advanced_split.h"
#include "delimiter_comparators.h"
#include <libft.h>
#include "strs_utils.h"
///////////////////////////////////
#include <stdio.h>

static int	handle_end_of_string(int *continue_flag)
{
	int	count;

	count = 0;
	while (g_input_str[count])
	{
		if ((g_input_str[count] == '>' || g_input_str[count] == '<')
				&& !(is_mirrored(g_input_str, count)) &&
				only_spaces_after(g_input_str, count))
		{
			print_reading_error("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		if (g_input_str[count] == '|' && !(is_mirrored(g_input_str, count)) &&
				only_spaces_after(g_input_str, count))
		{
			*continue_flag = NEW_LINE;
			write (1, "> ", 2);
			return (0);
		}
		count++;
	}
	return (1);
}

static void	syntax_by_pipes(int *continue_flag, char **piped_strs, int last_open)
{
	int	j;

	j = 0;
	while (piped_strs[j] && piped_strs[j + last_open] && *continue_flag == 0)
	{
		if (!(is_piped_syntax_correct(piped_strs[j])))
		{
			if (last_open)
				print_reading_error("minishell: syntax error near unexpected token `newline'\n");
			else
				print_reading_error("minishell: syntax error near unexpected token `|'\n");
			*continue_flag = 1;
		}
		j++;
	}
}

static void	syntax_by_semicolones(char *noquotes, int last_open, int *continue_flag)
{
	char	**semicoloned_strs;
	char	**piped_strs;
	int	i;

	i = 0;
	if (!(semicoloned_strs = advanced_split(noquotes, is_semicolon, 0)))
		*continue_flag = MALLOC_ERROR;
	while (semicoloned_strs[i]  && *continue_flag == 0)
	{
		if (semicoloned_strs[i + last_open])
			if (!(is_semicoloned_syntax_correct(semicoloned_strs[i])))
			{
				print_reading_error("minishell: syntax error near unexpected token `;'\n");
				*continue_flag = 1;
			}
		if (!(piped_strs = advanced_split(semicoloned_strs[i], is_pipe, 0)))
			*continue_flag = MALLOC_ERROR;
		syntax_by_pipes(continue_flag, piped_strs, last_open);
		free_str_arr(&piped_strs);
		++i;
	}
	free_str_arr(&semicoloned_strs);
}

int	is_read_syntax_ok(int *continue_flag)
{
	int		last_open;
	char	*noquotes;

	if (!(noquotes = remove_quoted_str(g_input_str)))
	{
		*continue_flag = MALLOC_ERROR;
		return (0);
	}
	if (is_string_error(noquotes))
		return (0);
	last_open = !ends_with_semicolon(g_input_str);
	syntax_by_semicolones(noquotes, last_open, continue_flag);
	if (*continue_flag)
		return (0);
	if (last_open)
		return (handle_end_of_string(continue_flag));
	return (1);
}
