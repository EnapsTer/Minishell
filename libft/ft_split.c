/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:11:18 by aherlind          #+#    #+#             */
/*   Updated: 2020/11/04 13:11:20 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_words(char **words, int words_count)
{
	int i;

	i = 0;
	while (i < words_count)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

static int	words_len(char const *s, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static int	count_words(char const *s, char c)
{
	int i;
	int words_count;

	words_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words_count++;
		i++;
	}
	return (words_count);
}

static char	**fill_words(char const *s, int words_count, char c, char **words)
{
	int i;
	int j;
	int len;

	i = 0;
	while (i < words_count)
	{
		while (*s == c)
			s++;
		len = words_len(s, c);
		words[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!words[i])
			return (free_words(words, i));
		j = 0;
		while (j < len)
			words[i][j++] = *s++;
		words[i][j] = '\0';
		i++;
	}
	words[i] = NULL;
	return (words);
}

char		**ft_split(char const *s, char c)
{
	char	**words;
	int		words_count;

	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!words)
		return (NULL);
	words = fill_words(s, words_count, c, words);
	return (words);
}
