/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/04 12:15:55 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advanced_split.h"
#include "minishell.h"
#include "commands.h"
#include "delimiter_comparators.h"
#include <stdlib.h>
#include <stdio.h>

//предварительный парсинг на ошибки ; ' "
// капс команды
//
int main()
{
//	char **strs;
//	strs = advanced_split("echo ; echo", is_semicolon, 0);
//	if (!strs)
//	{
//		printf("ERROR BLYAT!!!");
//		return (0);
//	}
//	while (*strs)
//	{
////		char **redirect = advanced_split(*strs, '>', 1);
////		if (redirect)
////		{
////			while (*redirect)
////			{
////				printf("[%s]\n", *redirect);
////				redirect++;
////			}
////		}
//		printf("|%s|\n", *strs);
//		strs++;
//	}

// возвращать двойной указатель вместо 1
//
	char *str = "echo asd''asd";
	execute_commands(str);
	return (0);
}