/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:17:21 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/26 17:33:56 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADVANCED_SPLIT_UTILS_H
#define ADVANCED_SPLIT_UTILS_H

BOOL change_shield_char (char *shield_char, char *str, char delim, int shield);

int		get_str_len(char *str, char delimiter, int shielding);

int		fill_strs(char **strs, char *str, char delimiter, int shielding);

int		count_strs(char *str, char delimiter, int shielding);

char	*get_filled_str(char **str, char delimiter, int shielding);
#endif
