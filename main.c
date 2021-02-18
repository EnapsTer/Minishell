/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/18 17:21:09 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advanced_split.h"
#include "minishell.h"
#include "command_handlers.h"
#include "delimiter_comparators.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// выводить errno
// exit code $?
// предварительный парсинг на ошибки ; ' "
// капс команды
// cat | ls
// тест на закрытие in fd пример
// echo "\$" ------ echo '\$'
int main(int argc, char **argv, char **envp)
{
	char *str = "cat | ls";
	//ввод
	//предварительный парсинг
	if (handle_commands(str, envp) == -1)
		return (-1);
	return (0);
}