/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:17:21 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/31 15:36:47 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADVANCED_SPLIT_UTILS_H
#define ADVANCED_SPLIT_UTILS_H

BOOL change_shield_char (char *shield_char, char *str, int (*is_delimiter)(char *), int shield);

int		get_str_len(char *str, int (*is_delimiter)(char *), int shielding);

int		fill_strs(char **strs, char *str, int (*is_delimiter)(char *), int shielding);

int		count_strs(char *str, int (is_delimiter)(char *), int shielding);

char	*get_filled_str(char **str, int (*is_delimiter)(char *), int shielding);
#endif
