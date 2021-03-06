/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:45 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 17:54:13 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_UTILS_H
# define ENVIRONMENT_UTILS_H
# include "start.h"

char	*get_env_value(char *name, t_env **env);

char	**build_envp(t_env **env);

#endif
