/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:50:28 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/28 15:50:49 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRS_UTILS_H
#define STRS_UTILS_H

int		str_arr_len(char **arr);

int		str_arr_append(char ***arr, char *line);

void	free_str_arr(char ***arr);

int		ft_unregister_strcmp(char *s1, char *s2);

#endif
