/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_new_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:27:49 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/18 19:23:41 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "start.h"
#include "advanced_split.h"
#include "delimiter_comparators.h"
#include <libft.h>
#include "strs_utils.h"

static int	handle_end_of_string(int *continue_flag, t_env **env)
{
	int	count;

	count = 0;
	while (g_input_str[count])
	{
		if ((g_input_str[count] == '>' || g_input_str[count] == '<')
				&& !(is_mirrored(g_input_str, count)) &&
				only_spaces_after(g_input_str, count))
		{
			print_syntax_error("`newline'", env, continue_flag);
			return (0);
		}
		if (g_input_str[count] == '|' && !(is_mirrored(g_input_str, count)) &&
				only_spaces_after(g_input_str, count))
		{
			*continue_flag = NEW_LINE;
			write(1, "> ", 2);
			return (0);
		}
		count++;
	}
	return (1);
}

static void	syntax_by_pipes(int *continue_flag,
		char **piped_strs, int last_open, t_env **env)
{
	int	j;

	j = 0;
	if (only_spaces_after(piped_strs[0], -1))
	{
		print_syntax_error("token `|'", env, continue_flag);
		return ;
	}
	while (piped_strs[j] && piped_strs[j + last_open] && *continue_flag == 0)
	{
		if (!(is_piped_syntax_correct(piped_strs[j])) ||
				only_spaces_after(piped_strs[j + 1], -1))
		{
			if (last_open)
				print_syntax_error("token `newline'", env, continue_flag);
			else
				print_syntax_error("token `|'", env, continue_flag);
		}
		j++;
	}
}

static void	syntax_by_semicolones(char *noquotes,
		int last_open, int *continue_flag, t_env **env)
{
	char	**semicoloned_strs;
	char	**piped_strs;
	int		i;

	i = 0;
	if (!(semicoloned_strs = advanced_split(noquotes, is_semicolon, 0)))
		*continue_flag = MALLOC_ERROR;
	while (semicoloned_strs[i] && *continue_flag == 0)
	{
		if (semicoloned_strs[i + last_open])
			if (!(is_semicoloned_syntax_correct(semicoloned_strs[i])))
				print_syntax_error("token `;'", env, continue_flag);
		if (!(piped_strs = advanced_split(semicoloned_strs[i], is_pipe, 0)))
			*continue_flag = MALLOC_ERROR;
		syntax_by_pipes(continue_flag, piped_strs, last_open, env);
		free_str_arr(&piped_strs);
		++i;
	}
	free_str_arr(&semicoloned_strs);
}

int			is_read_syntax_ok(int *continue_flag, t_env **env)
{
	int		last_open;
	char	*noquotes;
	int		out;

	out = 1;
	last_open = !ends_with_semicolon(g_input_str);
	if (!(noquotes = remove_quoted_str(g_input_str, env, continue_flag)))
		out = 0;
	else if (is_string_error(noquotes, env, continue_flag))
		out = 0;
	if (out)
	{
		syntax_by_semicolones(noquotes, last_open, continue_flag, env);
		if (*continue_flag)
			out = 0;
		else if (last_open)
			out = handle_end_of_string(continue_flag, env);
	}
	nullify_str(&noquotes);
	return (out);
}
