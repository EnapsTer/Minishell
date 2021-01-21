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
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define BOOL int

char	**advanced_split(char *str, char delimiter, int shielding);
#endif
