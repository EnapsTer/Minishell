/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/02/10 13:38:11 by aherlind         ###   ########.fr       */
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
// поменять глобальное имя на гите чтоб статистика сохранялась
// предварительный парсинг на ошибки ; ' "
// капс команды
//
int main(int argc, char **argv, char **envp)
{
	char *str = "echo asd qwer";
	handle_commands(str, envp);
//	pid_t pid;
//	pid_t pid1;
//	pid_t pid2;
//	int status;
//	int rv;
//
//	int i = 0;
//	int a = 0;
//	while (i < 3)
//	{
//		pid = fork();
//		if (pid == 0)
//		{
//			sleep(i * 3);
//			printf("Мой PID -- %d PID родителя -- %d %d\n", getpid(), getppid(), a++);
//			exit(1);
//		}
//		else
//		{
//			i++;
//		}
//	}
//	while (wait(&status) > 0)
//		;
//	sswitch(pid=fork()) {
//		case -1:
//			perror("fork"); /* произошла ошибка */
//			exit(1); /*выход из родительского процесса*/
//		case 0:
//			printf(" CHILD: Это процесс-потомок!\n");
//			printf(" CHILD: Мой PID -- %d\n", getpid());
//			printf(" CHILD: PID моего родителя -- %d\n",
//				   getppid());
//			printf(" CHILD: Введите мой код возврата(как можно меньше):");
//			scanf(" %d");
//			printf(" CHILD: Выход!\n");
//			exit(rv);
//		default:
//			printf("PARENT: Это процесс-родитель!\n");
//			printf("PARENT: Мой PID -- %d\n", getpid());
//			printf("PARENT: PID моего потомка %d\n",pid);
//			printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
//			wait(&status);
//			printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
//			printf("PARENT: Выход!\n");
//	}
	return (0);
}