/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:24:09 by aherlind          #+#    #+#             */
/*   Updated: 2020/11/10 16:24:11 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);

char	*ft_gnl_strdup(char *s1);

size_t	ft_gnl_strlen(char *s);

char	*ft_gnl_strjoin(char *s1, char *s2);

int		index_of_char(char *s, char c);
#endif
