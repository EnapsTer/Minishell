/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_io_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:33:45 by aherlind          #+#    #+#             */
/*   Updated: 2021/03/18 18:24:33 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_UTILS_H
# define COMMANDS_UTILS_H

int		close_fd(int fd);

int		get_dr(char *file_name, int current_fd);

int		get_rr(char *file_name, int current_fd);

int		get_lr(char *file_name, int current_fd);

int		init_command(t_command *command);

void	free_command(t_command **command);

void	free_commands(t_command ***commands);

int		init_stdfd(t_fd *stdfd);

void	handle_exit(int commands_len);

#endif
