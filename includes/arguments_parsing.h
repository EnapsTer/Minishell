/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:26:47 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/10 17:34:47 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_PARSING_H
#define ARGUMENTS_PARSING_H

char	**get_arguments(char *str, t_env *env);

BOOL 	change_shield_char_value(char *shield_char, char *str);

BOOL is_masked(char *str, char shield_char);

char 	*get_value_str(char *str);

int 	skip_words(char *str);

#endif
