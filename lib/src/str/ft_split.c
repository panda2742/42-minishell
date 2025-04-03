/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:04:45 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:04:45 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_str.h"

static size_t	_count_words(char const *s, const char *charset);
static int		_bufcpy(
					char **result,
					size_t w,
					const char *s,
					const char *charset);
static t_bool	_is_in_charset(char c, const char *charset);

char	**ft_split(char const *s, const char *charset)
{
	size_t	word_count;
	size_t	w;
	char	**tabstr;
	int		_bufcpyres;

	word_count = _count_words(s, charset);
	tabstr = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!tabstr)
		return (NULL);
	w = 0;
	while (w < word_count)
	{
		while (*s && _is_in_charset(*s, charset))
			s++;
		_bufcpyres = _bufcpy(tabstr, w, s, charset);
		if (_bufcpyres == -1)
			return (NULL);
		s += _bufcpyres;
		w++;
	}
	tabstr[word_count] = NULL;
	return (tabstr);
}

static size_t	_count_words(char const *s, const char *charset)
{
	size_t	word_count;

	word_count = 0;
	while (*s && _is_in_charset(*s, charset))
		s++;
	while (*s)
	{
		while (*s && _is_in_charset(*s, charset))
			s++;
		if (*s && !_is_in_charset(*s, charset))
			word_count++;
		while (*s && !_is_in_charset(*s, charset))
			s++;
	}
	return (word_count);
}

static int	_bufcpy(char **result, size_t w, const char *s, const char *charset)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (_is_in_charset(*s, charset) && *s)
		s++;
	while (_is_in_charset(s[len], charset) && s[len])
		len++;
	result[w] = (char *)malloc((len + 1) * sizeof(char));
	if (!result[w])
	{
		while (w)
			free(result[--w]);
		free(result);
		return (-1);
	}
	i = 0;
	while (i < len && s[i])
	{
		result[w][i] = s[i];
		i++;
	}
	result[w][i] = '\0';
	return (len + 1);
}

static t_bool	_is_in_charset(char c, const char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (true);
		charset++;
	}
	return (false);
}
