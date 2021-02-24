/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:53:45 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/19 17:53:46 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SPLIT_H
#define MINISHELL_SPLIT_H

char	**advanced_split(char *str, int (*is_delimiter)(char *), int shielding);

#endif
