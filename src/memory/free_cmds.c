/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:34 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/13 11:18:32 by ehosta           ###   ########.fr       */
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

static void	_free_cmd_redirect(t_excmd *cmd)
{
	if (cmd->in_redirects.size)
	{
		if (cmd->in_redirects.final_fd.fd > STDERR_FILENO)
			close(cmd->in_redirects.final_fd.fd);
		cmd->in_redirects.final_fd.fd = -1;
		_free_redirect_manager(&cmd->in_redirects);
	}
	if (cmd->out_redirects.size)
	{
		if (cmd->out_redirects.final_fd.fd > STDERR_FILENO)
			cmd->out_redirects.final_fd.fd = -1;
		_free_redirect_manager(&cmd->out_redirects);
	}
}

void	free_one_cmd(t_excmd *cmd)
{
	if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	if (cmd->argv && cmd->argv != empty_tab())
	{
		if (cmd->argv[0])
			ft_free_strtab(cmd->argv);
		else
			free(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->paths[0] && cmd->paths != empty_paths())
	{
		ft_free_strtab(cmd->paths);
		cmd->argv = NULL;
	}
	_free_cmd_redirect(cmd);
	free(cmd);
}

static void	_free_redirect(t_redir *elt)
{
	if (elt->filepath)
	{
		free(elt->filepath);
		elt->filepath = NULL;
	}
	if (elt->heredoc_del)
	{
		free(elt->heredoc_del);
		elt->heredoc_del = NULL;
	}
}

static void	_free_redirect_manager(t_redir_manager *manager)
{
	size_t	i;
	t_redir	*elt;
	t_redir	*tmp;

	i = -1;
	if (manager->redirects == NULL)
		return ;
	elt = *manager->redirects;
	while (++i < manager->size && elt)
	{
		_free_redirect(elt);
		tmp = elt->next;
		free(elt);
		elt = tmp;
	}
	free(manager->redirects);
}
