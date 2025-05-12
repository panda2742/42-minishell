/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 10:40:51 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hdfrag	*_convert_line_to_frags(char *line);
static void		_free_frags(t_hdfrag *frag);

t_exit	heredoc(char *buffer, char *del, t_bool skip_writing)
{
	char		*line;
	t_hdfrag	*first;
	t_hdfrag	*elt;

	(void)first;
	(void)elt;
	(void)del;
	(void)_convert_line_to_frags;
	(void)_free_frags;
	while (1)
	{
		line = readline("> ");
		if (buffer && !skip_writing)
			buffer = line;
		if (strcmp(line, del) == 0)
			break ;
	}
	return (EXIT_SUCCESS);
}

static t_hdfrag	*_create_hdfrag(void)
{
	t_hdfrag	*res;

	res = ft_memalloc(sizeof(t_hdfrag));
	if (res == NULL)
		return (NULL);
	ft_bzero(res->buffer, HD_FRAG_BUFFER);
	res->len = 0;
	res->total_len = 0;
	res->next = NULL;
	return (res);
}

static t_hdfrag	*_convert_line_to_frags(char *line)
{
	t_hdfrag	*first;
	t_hdfrag	*frag;
	t_hdfrag	*new_frag;
	uint16_t	i;
	uint16_t	j;

	frag = NULL;
	i = -1;
	j = -1;
	while (line[++i])
	{
		++j;
		if (frag == NULL)
		{
			frag = _create_hdfrag();
			first = frag;
		}
		if (i >= HD_FRAG_BUFFER)
		{
			new_frag = _create_hdfrag();
			new_frag->total_len = frag->total_len;
			frag->next = new_frag;
			frag = new_frag;
			j = 0;
		}
		frag->buffer[j] = line[i];
		frag->len++;
		frag->total_len++;
	}
	return (first);
}

static void	_free_frags(t_hdfrag *frag)
{
	t_hdfrag	*tmp;

	while (frag)
	{
		tmp = frag->next;
		ft_bzero(frag->buffer, HD_FRAG_BUFFER);
		frag = tmp;
	}
}
