/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:10:49 by nscarab           #+#    #+#             */
/*   Updated: 2021/02/21 19:47:46 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_H
#define START_H

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

char	*superstrjoin(char *s1, char *s2);
#endif
