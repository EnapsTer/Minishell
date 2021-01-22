/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <aherlind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:11:26 by aherlind          #+#    #+#             */
/*   Updated: 2021/01/22 18:08:17 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advanced_split.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char **strs;
	strs = advanced_split("echo > '>' ';'", ';', 1);
	while (*strs)
	{
		printf("|%s|\n", *strs);
		strs++;
	}
}