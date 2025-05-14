/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:51 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 15:55:47 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_try_open(t_redir *last, t_redir_manager *redirects_manager);
static t_redir	*_continue_loop(t_redir *last);

static void	_set_heredoc(t_redir *last)
{
	last->fd.fd = open(last->filepath, O_RDONLY);
	last->fd.type = STREAM_REDIR;
}

static void	_set_last(t_redir_manager *redirects_manager, t_redir *last)
{
	redirects_manager->last = last;
	redirects_manager->final_fd.fd = last->fd.fd;
	redirects_manager->final_fd.type = last->fd.type;
}

t_redir	*get_last_redirect(t_redir_manager *redirects_manager)
{
	t_redir	*last;

	if (redirects_manager->size == 0)
		return (NULL);
	last = *redirects_manager->redirects;
	while (last)
	{
		last->fd.fd = -1;
		if (!last->filepath && !last->is_heredoc)
			return (mem_redir_fail(redirects_manager, last));
		if (last->is_heredoc && last->next == NULL)
			_set_heredoc(last);
		if (last->is_heredoc && last->next == NULL)
			break ;
		else if (_try_open(last, redirects_manager) == false)
			return (NULL);
		if (last->next)
		{
			last = _continue_loop(last);
			continue ;
		}
		break ;
	}
	_set_last(redirects_manager, last);
	return (last);
}

static t_bool	_try_open(t_redir *last, t_redir_manager *redirects_manager)
{
	if (redirects_manager->type == IN_REDIR && !last->is_heredoc)
		last->fd.fd = open(last->filepath, O_RDONLY);
	else if (redirects_manager->type == OUT_REDIR)
	{
		if (last->out_append_mode)
			last->fd.fd = open(last->filepath, O_RDWR | O_CREAT | O_APPEND,
					0644);
		else
			last->fd.fd = open(last->filepath, O_RDWR | O_CREAT | O_TRUNC,
					0644);
	}
	if (last->fd.fd == -1 && !last->is_heredoc)
	{
		redirects_manager->problematic = last;
		if (last->filepath)
			puterr(ft_sprintf(": %s", last->filepath), true);
		else
			puterr(ft_sprintf(": (invalid filename)"), true);
		return (false);
	}
	return (true);
}

static t_redir	*_continue_loop(t_redir *last)
{
	if (last->fd.fd > STDERR_FILENO)
		close(last->fd.fd);
	last->fd.fd = -1;
	return (last->next);
}
