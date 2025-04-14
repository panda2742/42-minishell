/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:26:25 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/09 22:26:28 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_c(char c, char s)
{
	if (s == c)
		return (1);
	else
		return (0);
}

static size_t	ft_word(char *s, char c)
{
	size_t	i;
	size_t	w_count;

	w_count = 0;
	i = 0;
	while (s[i])
	{
		if (is_c(c, s[i]))
			i++;
		else if (!is_c(c, s[i]))
		{
			w_count++;
			while (!is_c(c, s[i]) && s[i])
				i++;
		}
	}
	return (w_count);
}

static void	to_free(char **tab, int word)
{
	while (word >= 0)
		free(tab[word--]);
	free(tab);
}

static char	**tab_malloc(char c, char const *s, char **tab, size_t i)
{
	size_t	word;
	size_t	pos;

	word = 0;
	while (s[i])
	{
		pos = i;
		if (is_c(c, s[i]))
			i++;
		else if (!is_c(c, s[i]))
		{
			while (!is_c(c, s[i]) && s[i])
				i++;
			tab[word] = ft_substr(s, pos, i - pos);
			if (!tab[word])
			{
				to_free(tab, word);
				return (NULL);
			}
			word++;
		}
	}
	tab[word] = NULL;
	return (tab);
}

char	**ft_split_a(char const *s, char c)
{
	char	**tab;
	size_t	i;

	i = 0;
	tab = malloc((ft_word((char *)s, c) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	return (tab_malloc(c, s, tab, i));
}
