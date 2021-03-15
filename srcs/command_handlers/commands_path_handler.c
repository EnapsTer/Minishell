/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:20:19 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/15 17:04:24 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "delimiter_comparators.h"
#include "advanced_split.h"
#include "strs_utils.h"
#include <stdlib.h>
#include <dirent.h>
#include "start.h"
#include "environment_utils.h"
#include <string.h>

int		is_in_directory(char *file_name, char *path)
{
	DIR				*dir;
	struct dirent	*dir_file;

	if (!(dir = opendir(path)))
		return (ERROR);
	while ((dir_file = readdir(dir)))
	{
		if (!ft_strcmp(file_name, dir_file->d_name))
		{
			closedir(dir);
			return (TRUE);
		}
	}
	closedir(dir);
	return (FALSE);
}

char	*create_full_path(char *name, char *path)
{
	char	*result;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(path) + 1;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(result, path, len + 1);
	ft_strlcat(result, "/", len + 1);
	ft_strlcat(result, name, len + 1);
	return (result);
}

char	*get_command_path(char *name, t_env **env)
{
	char	*path;
	char	**env_path;
	int		i;

	if (ft_strchr(name, '/'))
		return (name);
	i = 0;
	if (!(env_path = advanced_split(get_env_value("PATH", env), is_colon, 0)))
		return (NULL);
	while (env_path[i])
	{
		if (is_in_directory(name, env_path[i]))
		{
			if (!(path = create_full_path(name, env_path[i])))
				return (NULL);
			free_str_arr(&env_path);
			return (path);
		}
		i++;
	}
	free_str_arr(&env_path);
	return (NULL);
}
