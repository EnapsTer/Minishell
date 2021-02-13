/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:27:02 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/11 14:16:22 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "advanced_split.h"
#include "libft.h"
#include "strs_utils.h"
#include "delimiter_comparators.h"
#include <stdlib.h>

char	*get_env_value(char *name, char **envp)
{
	int		i;
	char 	**strs;
	char	*result;

	i = 0;
	while (envp[i])
	{
		if (!(strs = advanced_split(envp[i], is_equal, 0)))
			return (NULL);
		if (!ft_strcmp(name, strs[0]))
		{
			result = ft_strdup(strs[1]);
			free_str_arr(&strs);
			return (result);
		}
		free_str_arr(&strs);
		i++;
	}
	return (NULL);
}