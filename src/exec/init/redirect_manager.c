/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:51 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/10 11:37:24 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_try_open(t_redir *last, t_redir_manager *redirects_manager);
static t_redir	*_continue_loop(t_redir *last);

void	read_heredocs(t_redir_manager *redirects_manager)
{
	t_redir	*elt;
	size_t	nb_heredoc;

	nb_heredoc = -1;
	elt = *redirects_manager->redirects;
	while (elt)
	{
		if (elt->is_heredoc)
		{
			nb_heredoc++;
			elt->heredoc_id = nb_heredoc;
		}
		elt = elt->next;
	}
	elt = *redirects_manager->redirects;
	while (elt)
	{
		if (elt->is_heredoc)
			heredoc(
				elt->heredoc_del,
				elt->heredoc_content,
				elt->heredoc_id != nb_heredoc);
		elt = elt->next;
	}
}

t_redir	*mem_redir_fail(t_redir_manager *redirects_manager, t_redir *last)
{
	redirects_manager->problematic = last;
	puterr(ft_sprintf(": error: Memory allocation error (redirects)\n"), false);
	return (NULL);
}


t_redir	*get_last_redirect(t_redir_manager *redirects_manager)
{
	t_redir	*last;

	if (redirects_manager->size == 0)
		return (NULL);
	if (redirects_manager->type == IN_REDIR)
		read_heredocs(redirects_manager);
	last = *redirects_manager->redirects;
	while (last)
	{
		last->fd.fd = -1;
		if (!last->filepath && !last->is_heredoc)
			return (mem_redir_fail(redirects_manager, last));
		if (_try_open(last, redirects_manager) == false)
			return (NULL);
		if (last->next)
		{
			last = _continue_loop(last);
			continue ;
		}
		break ;
	}
	redirects_manager->last = last;
	redirects_manager->final_fd = last->fd;
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
