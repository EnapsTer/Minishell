/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_io_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:33:45 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/09 12:33:45 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_IO_UTILS_H
#define COMMANDS_IO_UTILS_H

int		close_fd(int fd);

int 	get_double_redirect_fd(char *file_name, int current_fd);

int 	get_right_redirect_fd(char *file_name, int current_fd);

int 	get_left_redirect_fd(char *file_name, int current_fd);

int			init_command(t_command *command);

void		free_command(t_command **command);

void		free_commands(t_command ***commands);

int 		init_stdfd(t_fd *stdfd);
#endif
