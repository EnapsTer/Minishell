/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:31:34 by nscarab           #+#    #+#             */
/*   Updated: 2021/03/12 23:03:47 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	only_spaces_after(char *str, int i)
{
	if (!str)
		return (1);
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	}
	return (1);
}

int	only_spaces_before(char *str, int i)
{
	if (!str)
		return (1);
	while (--i >= 0)
	{
		if (str[i] != ' ' || str[i] != '\t')
			return (0);
	}
	return (1);
}

int	is_mirrored(char *str, int i)
{
	int	count;

	count = 0;
	while (--i >= 0)
	{
		if (str[i] == '\\')
			count++;
		else
			break ;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

int	ends_with_semicolon(char *str)
{
	int	count;

	count = 0;
	if (!str || !*str)
		return (0);
	while (str[count + 1])
		count++;
	if (str[count] == ';')
		return (1);
	return (0);
}
