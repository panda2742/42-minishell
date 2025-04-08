#include "minishell.h"

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
			heredoc(elt->heredoc_del, elt->heredoc_content, elt->heredoc_id != nb_heredoc);
		elt = elt->next;
	}
}

t_redir	*get_last_redirect(t_redir_manager *redirects_manager)
{
	t_redir	*last;

	if (redirects_manager->size == 0)
		return (NULL);
	last = *redirects_manager->redirects;
	while (last->next)
	{
		last->fd = -1;
		if (!last->filepath)
			return (NULL);
		if (redirects_manager->type == IN_REDIR)
			last->fd = open(last->filepath, O_RDONLY);
		else if (redirects_manager->type == OUT_REDIR)
			last->fd = open(last->filepath, O_RDWR | O_CREAT | ((last->out_append_mode * O_APPEND) + (!last->out_append_mode * O_TRUNC)));
		if (last->fd == -1)
			return (NULL);
		if (last->next)
			close(last->fd);
		last = last->next;
	}
	return (last);
}
