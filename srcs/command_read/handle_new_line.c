/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_new_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:27:49 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/03 15:51:58 by nscarab          ###   ########.fr       */
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

int	handle_end_of_string(int *continue_flag)
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
			*continue_flag = 2;
			write (1, "> ", 2);
			return (0);
		}
		count++;
	}
	return (1);
}

void	handle_semicoloned_syntax(int *continue_flag, char *str)
{
	if (!(is_semicoloned_syntax_correct(str)))
	{
		print_reading_error("minishell: syntax error near unexpected token `;'\n");
		*continue_flag = 1;
	}
}

void	handle_piped_syntax(int *continue_flag, char *str, int last_open)
{
	if (!(is_piped_syntax_correct(str)))
	{
		if (last_open)
			print_reading_error("minishell: syntax error near unexpected token `newline'\n");
		else
			print_reading_error("minishell: syntax error near unexpected token `|'\n");
		*continue_flag = 1;
	}
}

char *remove_quoted_str(char *str)
{
	char	*out;
	int	strlen;
	int	quote_flag;
	int	i;

	if (!str || str[0] == '\0')
	{
		out = ft_strdup("");
		return (out);
	}
	quote_flag = 0;
	i = 0;
	strlen = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !is_mirrored(str, i))
		{
			if (quote_flag == 1 && quote_flag != 2)
				quote_flag = 0;
			else if (quote_flag != 2)
			{
				strlen++;
				quote_flag = 1;
			}
		}
		else if (str[i] == '"' && !is_mirrored(str, i))
		{
			if (quote_flag == 2 && quote_flag != 1)
				quote_flag = 0;
			else if (quote_flag != 1)
			{
				strlen++;
				quote_flag = 2;
			}
		}
		else if (quote_flag > 0)
			;
		else
			strlen++;
		i++;
	}
	out = (char*)malloc(sizeof(char) * (strlen + 1));
	strlen = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !is_mirrored(str, i))
		{
			if (quote_flag == 1 && quote_flag != 2)
				quote_flag = 0;
			else if (quote_flag != 2)
			{
				out[strlen++] = '\r';
				quote_flag = 1;
			}
		}
		else if (str[i] == '"' && !is_mirrored(str, i))
		{
			if (quote_flag == 2 && quote_flag != 1)
				quote_flag = 0;
			else if (quote_flag != 1)
			{
				out[strlen++] = '\r';
				quote_flag = 2;
			}
		}
		else if (quote_flag > 0)
			;
		else
			out[strlen++] = str[i];
		i++;
	}
	out[strlen] = '\0';
	return (out);
}

int	is_read_syntax_ok(int *continue_flag)
{
	int	i;
	int	j;
	int	last_open;
	char	**semicoloned_strs;
	char	**piped_strs;
	char	*noquotes;

	*continue_flag = 0;
	last_open = 0;
	i = 0;
	noquotes = remove_quoted_str(g_input_str);
	//ft_putstr_fd(noquotes, 1);
	if (is_string_error(noquotes))
		return (0);
	last_open = !ends_with_semicolon(g_input_str);
	semicoloned_strs = advanced_split(noquotes, is_semicolon, 0);
	while (semicoloned_strs[i]  && *continue_flag == 0)
	{
		//printf("%s, %d", semicoloned_strs[i], i);
		if (semicoloned_strs[i + last_open])
			handle_semicoloned_syntax(continue_flag, semicoloned_strs[i]);
		if (!(piped_strs = advanced_split(semicoloned_strs[i], is_pipe, 0)))
			return (0);
		j = 0;
		while (piped_strs[j] && piped_strs[j + last_open] && *continue_flag == 0)
			handle_piped_syntax(continue_flag, piped_strs[j++], last_open);
		free_str_arr(&piped_strs);
		++i;
	}
	free_str_arr(&semicoloned_strs);
	if (*continue_flag)
		return (0);
	if (last_open)
		return (handle_end_of_string(continue_flag));
	return (1);
}
