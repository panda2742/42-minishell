/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:51 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/13 10:43:22 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_try_open(t_redir *last, t_redir_manager *redirects_manager);
static t_redir	*_continue_loop(t_redir *last);
static void		_read_heredocs(t_redir_manager *redirects_manager);
static int		_write_heredoc(char *buffer, char **filepath);

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
		_read_heredocs(redirects_manager);
	last = *redirects_manager->redirects;
	while (last)
	{
		last->fd.fd = -1;
		if (!last->filepath && !last->is_heredoc)
			return (mem_redir_fail(redirects_manager, last));
		if (last->is_heredoc && last->next == NULL)
		{
			last->fd.fd = _write_heredoc(last->heredoc_content, &last->filepath);
			last->fd.type = STREAM_REDIR;
			break ;
		}
		else if (_try_open(last, redirects_manager) == false)
			return (NULL);
		if (last->next)
		{
			last = _continue_loop(last);
			continue ;
		}
		break ;
	}
	redirects_manager->last = last;
	redirects_manager->final_fd.fd = last->fd.fd;
	redirects_manager->final_fd.type = last->fd.type;
	return (last);
}

static void	_read_heredocs(t_redir_manager *redirects_manager)
{
	t_redir	*elt;
	size_t	nb_heredoc;
	t_exit	heredoc_status;

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
		{
			heredoc_status = heredoc(
				&elt->heredoc_content,
				elt->heredoc_del,
				elt->heredoc_id != nb_heredoc && elt->next == NULL);
		}
		elt = elt->next;
	}
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

static int	_write_heredoc(char *buffer, char **filepath)
{
	ssize_t	buffer_len;
	char	*random_id;
	int		heredoc_fd;

	random_id = get_random_chars(24);
	*filepath = ft_sprintf("/tmp/minishell_heredoc_%s", random_id);
	heredoc_fd = open(*filepath, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(random_id);
	if (heredoc_fd == -1)
		return (-1);
	buffer_len = (ssize_t)ft_strlen(buffer);
	while ((buffer_len - 4096) > 0)
	{
		if (write(heredoc_fd, buffer, 4096))
		{
			free(buffer);
			return (heredoc_fd);
		}
		buffer += 4096;
		buffer_len -= 4096;
	}
	write(heredoc_fd, buffer, buffer_len);
	free(buffer);
	close(heredoc_fd);
	return (open(*filepath, O_RDONLY));
}
