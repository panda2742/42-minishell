/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/13 14:17:27 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_write_heredoc(int fd, char *buffer);

t_exit	heredoc(char *del, char **filepath ,t_bool skip_writing)
{
	char		*line;
	char		*random_id;
	int			heredoc_fd;
	size_t		line_i;

	random_id = get_random_chars(24);
	*filepath = ft_sprintf("/tmp/minishell_heredoc_%s", random_id);
	heredoc_fd = open(*filepath, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(random_id);
	if (heredoc_fd == -1)
		return (EXIT_FAILURE);
	line_i = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			putwarn(ft_sprintf(": warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", line_i, del), false);
			break ;
		}
		line_i++;
		if (ft_strcmp(line, del) == 0)
			break ;
		if (skip_writing)
			continue ;
		_write_heredoc(heredoc_fd, line);
		write(heredoc_fd, "\n", 1);
	}
	close(heredoc_fd);
	return (EXIT_SUCCESS);
}

static int	_write_heredoc(int fd, char *buffer)
{
	ssize_t	buffer_len;

	buffer_len = (ssize_t)ft_strlen(buffer);
	while ((buffer_len - 65536) > 0)
	{
		if (write(fd, buffer, 65536))
		{
			free(buffer);
			return (EXIT_FAILURE);
		}
		buffer += 65536;
		buffer_len -= 65536;
	}
	write(fd, buffer, buffer_len);
	free(buffer);
	return (EXIT_SUCCESS);
}

void	clear_every_tmpfile(t_excmd **cmds)
{
	t_excmd	*cmd;
	t_redir	*last;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->in_redirects.size == 0)
		{
			cmd = cmd->next;
			continue ;
		}
		last = *cmd->in_redirects.redirects;
		while (last)
		{
			if (last->is_heredoc && last->next == NULL)
				break ;
			last = last->next;
		}
		if (last)
			unlink(last->filepath);
		cmd = cmd->next;
	}
}
