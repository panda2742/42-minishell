/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:48 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/17 15:15:20 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_in_redirect(char *filepath)
{
	t_redir	*res;

	res = ft_memalloc(sizeof(t_redir));
	if (res == NULL)
		return (NULL);
	res->filepath = ft_strdup(filepath);
	if (res->filepath == NULL)
	{
		free(res);
		return (NULL);
	}
	res->fd.fd = -2;
	res->fd.type = STREAM_STD;
	res->is_heredoc = false;
	res->heredoc_id = -1;
	res->heredoc_del = NULL;
	res->heredoc_content = NULL;
	res->out_append_mode = false;
	res->next = NULL;
	return (res);
}

t_redir	*create_out_redirect(char *filepath, t_bool append_mode)
{
	t_redir	*res;

	res = ft_memalloc(sizeof(t_redir));
	if (res == NULL)
		return (NULL);
	res->filepath = ft_strdup(filepath);
	if (res->filepath == NULL)
	{
		free(res);
		return (NULL);
	}
	res->fd.fd = -2;
	res->fd.type = STREAM_STD;
	res->is_heredoc = false;
	res->heredoc_id = -1;
	res->heredoc_del = NULL;
	res->heredoc_content = NULL;
	res->out_append_mode = append_mode;
	res->next = NULL;
	return (res);
}

t_redir	*create_heredoc_redirect(char *delimiter)
{
	t_redir	*res;

	res = ft_memalloc(sizeof(t_redir));
	if (res == NULL)
		return (NULL);
	res->filepath = NULL;
	res->fd.fd = -2;
	res->fd.type = STREAM_STD;
	res->is_heredoc = true;
	res->heredoc_id = -1;
	res->heredoc_del = ft_strdup(delimiter);
	res->heredoc_content = NULL;
	res->out_append_mode = false;
	res->next = NULL;
	return (res);
}
