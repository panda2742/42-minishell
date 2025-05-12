/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 11:15:35 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hdfrag	*_convert_line_to_frags(t_hdfrag *prev, char *line);
static void		_free_frags(t_hdfrag *frag);
static void		_print_frags(t_hdfrag *frag);

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
	_print_frags(elt);
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
	frag->len++;
	frag->total_len++;
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

static void	_print_frags(t_hdfrag *frag)
{
	while (frag)
	{
		printf("[%s%p%s] -------------------\n", U_MAGENTA, frag, RESET);
		printf("[%s%p%s] buffer:\t%s%s%s\n", U_MAGENTA, frag, RESET, B_BLUE, frag->buffer, RESET);
		printf("[%s%p%s] len:\t%s%d%s\n", U_MAGENTA, frag, RESET, B_YELLOW, frag->len, RESET);
		printf("[%s%p%s] total_len:\t%s%d%s\n", U_MAGENTA, frag, RESET, B_YELLOW, frag->total_len, RESET);
		printf("[%s%p%s] pos:\t%s%zu%s\n", U_MAGENTA, frag, RESET, B_YELLOW, frag->pos, RESET);
		printf("[%s%p%s] next:\n", U_MAGENTA, frag, RESET);
		frag = frag->next;
	}
}
