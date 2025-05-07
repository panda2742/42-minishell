/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:34 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/06 18:54:03 by abonifac         ###   ########.fr       */
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
	// free(cmds); Je l ai commente car ca cree une erreur mais on va en avoir besoin je pense
}

void	free_one_cmd(t_excmd *cmd)
{
	if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	if (cmd->argv[0])
	{
		ft_free_strtab(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->paths[0])
	{
		ft_free_strtab(cmd->paths);
		cmd->argv = NULL;
	}
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
	free(cmd);
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
		if (elt->heredoc_content)
		{
			free(elt->heredoc_content);
			elt->heredoc_content = NULL;
		}
		tmp = elt->next;
		free(elt);
		elt = tmp;
	}
	free(manager->redirects);
}
