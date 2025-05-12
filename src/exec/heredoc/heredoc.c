/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 15:54:17 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hdfrag	*_convert_line_to_frags(t_hdfrag *prev, char *line);
static void		_free_frags(t_hdfrag *frag);
static char		*_convert_frags_to_string(t_hdfrag *frag, char *buffer);
static size_t	_raw_strlcpy(char *dst, const char *src, size_t size);

t_exit	heredoc(char *buffer, char *del, t_bool skip_writing)
{
	char		*line;
	t_hdfrag	*prev;
	t_hdfrag	*elt;
	t_hdfrag	*first;

	(void)buffer;
	prev = NULL;
	first = NULL;
	while (1)
	{
		line = readline("> ");
		if (strcmp(line, del) == 0)
			break ;
		if (skip_writing)
			continue ;
		elt = _convert_line_to_frags(prev, line);
		if (elt == NULL)
		{
			_free_frags(first);
			puterr(ft_sprintf(": error: Memory allocation error (heredoc)\n"), false);
			return (EXIT_FAILURE);
		}
		prev = elt;
		if (first == NULL)
			first = prev;
	}
	buffer = _convert_frags_to_string(first, buffer);
	_free_frags(first);
	printf("%s", buffer);
	return (EXIT_SUCCESS);
}

static t_hdfrag	*_create_hdfrag(void)
{
	t_hdfrag	*res;

	res = ft_memalloc(sizeof(t_hdfrag));
	if (res == NULL)
		return (NULL);
	res->buffer = NULL;
	res->len = 0;
	res->total_len = 0;
	res->next = NULL;
	res->pos = 1;
	return (res);
}

static t_hdfrag	*_convert_line_to_frags(t_hdfrag *prev, char *line)
{
	t_hdfrag	*frag;

	frag = _create_hdfrag();
	if (frag == NULL)
		return (NULL);
	if (prev)
	{
		frag->total_len = prev->total_len;
		frag->pos = prev->pos + 1;
		prev->next = frag;
	}
	else
	{
		frag->total_len = 0;
		frag->pos = 1;
	}
	frag->buffer = line;
	frag->len = ft_strlen(frag->buffer);
	frag->total_len += frag->len;
	return (frag);
}

static void	_free_frags(t_hdfrag *frag)
{
	t_hdfrag	*tmp;

	while (frag)
	{
		tmp = frag->next;
		if (frag->buffer)
			free(frag->buffer);
		free(frag);
		frag = tmp;
	}
}

static char	*_convert_frags_to_string(t_hdfrag *frag, char *buffer)
{
	t_hdfrag	*last;
	size_t		total_len;
	size_t		i;

	last = frag;
	while (last->next)
		last = last->next;
	total_len = last->total_len + last->pos;
	buffer = ft_memalloc(sizeof(char) * (total_len + 1));
	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (frag)
	{
		_raw_strlcpy(buffer + i, frag->buffer, frag->len + 1);
		i += frag->len;
		buffer[i] = '\n';
		i++;
		frag = frag->next;
	}
	buffer[total_len] = 0;
	return (buffer);
}

static size_t	_raw_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (!size)
		return (srclen);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}
