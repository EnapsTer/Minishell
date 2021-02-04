/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_comparators.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:39:10 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/31 15:39:10 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELIMITER_COMPARATORS_H
#define DELIMITER_COMPARATORS_H

int		is_semicolon(char *str);

int 	is_pipe(char *str);

int		is_redirect(char *str);

int 	is_redirect_and_space(char *str);

int 	is_shield(char *str);
#endif
