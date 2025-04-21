/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:34 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/21 16:29:57 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_free_redirect_manager(t_redir_manager *manager);

void	free_cmds(t_excmd **cmds)
{
	t_excmd	*cmd;
	t_excmd	*tmp;

	cmd = *cmds;
	while (cmd)
	{
		tmp = cmd->next;
		free_one_cmd(cmd);
		cmd = tmp;
	}
}

void	free_one_cmd(t_excmd *cmd)
{
	if (cmd->name)
		free(cmd->name);
	if (cmd->raw)
		free(cmd->raw);
	if (cmd->argv[0])
		ft_free_strtab(cmd->argv);
	if (cmd->in_redirects.size)
	{
		close(cmd->in_redirects.final_fd.fd);
		cmd->in_redirects.final_fd.fd = -1;
		_free_redirect_manager(&cmd->in_redirects);
	}
	if (cmd->out_redirects.size)
	{
		close(cmd->out_redirects.final_fd.fd);
		cmd->out_redirects.final_fd.fd = -1;
		_free_redirect_manager(&cmd->out_redirects);
	}
	free(cmd);
}

static void	_free_redirect_manager(t_redir_manager *manager)
{
	size_t	i;
	t_redir	*elt;
	t_redir	*tmp;

	i = -1;
	elt = *manager->redirects;
	while (++i < manager->size && elt)
	{
		if (elt->filepath)
			free(elt->filepath);
		if (elt->heredoc_del)
			free(elt->heredoc_del);
		if (elt->heredoc_content)
			free(elt->heredoc_content);
		tmp = elt->next;
		free(elt);
		elt = tmp;
	}
	free(manager->redirects);
}
