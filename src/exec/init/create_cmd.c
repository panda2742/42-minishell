/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:43 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/23 16:27:43 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_init_redirects(t_excmd *cmd);

t_excmd	*create_cmd(char *cmd_name, t_env_manager *env)
{
	t_excmd	*res;

	res = ft_memalloc(sizeof(t_excmd));
	if (!res)
		return (NULL);
	res->id = -1;
	res->name = NULL;
	if (cmd_name)
	{
		res->name = ft_strdup(cmd_name);
		if (res->name == NULL)
			return (NULL);
	}
	res->in_a_child = true;
	res->proto = NULL;
	res->argc = 0;
	res->argv = empty_tab();
	res->env = env;
	res->envp = empty_tab();
	res->raw = NULL;
	res->paths = empty_tab();
	res->prev = NULL;
	res->next = NULL;
	res->in_dup = NULL;
	res->out_dup = NULL;
	res->minishell = NULL;
	res->params = NULL;
	_init_redirects(res);
	return (res);
}

static void	_init_redirects(t_excmd *cmd)
{
	cmd->in_redirects.size = 0;
	cmd->out_redirects.size = 0;
	cmd->in_redirects.redirects = NULL;
	cmd->out_redirects.redirects = NULL;
	cmd->in_redirects.type = IN_REDIR;
	cmd->out_redirects.type = OUT_REDIR;
	cmd->in_redirects.has_heredoc = false;
	cmd->out_redirects.has_heredoc = false;
	cmd->in_redirects.last = NULL;
	cmd->out_redirects.last = NULL;
	cmd->in_redirects.final_fd.fd = STDIN_FILENO;
	cmd->in_redirects.final_fd.type = STREAM_STD;
	cmd->out_redirects.final_fd.fd = STDOUT_FILENO;
	cmd->out_redirects.final_fd.type = STREAM_STD;
	cmd->in_redirects.problematic = NULL;
	cmd->out_redirects.problematic = NULL;
	cmd->pipe_open[0] = false;
	cmd->pipe_open[1] = false;
	cmd->pipe[0] = 0;
	cmd->pipe[1] = 0;
}

t_redir	*add_redirect(t_excmd *cmd, t_redir_type type, t_redir *redirect)
{
	t_redir_manager	*manager;
	t_redir			*last;

	manager = &cmd->out_redirects;
	if (type == IN_REDIR)
	{
		manager = &cmd->in_redirects;
		if (manager->has_heredoc == false && redirect->is_heredoc)
			manager->has_heredoc = true;
	}
	if (manager->size == 0)
	{
		manager->redirects = ft_memalloc(sizeof(t_redir *));
		if (!manager->redirects)
			return (NULL);
		manager->redirects[0] = redirect;
		manager->size += 1;
		return (redirect);
	}
	last = *manager->redirects;
	while (last->next)
		last = last->next;
	last->next = redirect;
	manager->size += 1;
	return (redirect);
}

void	link_commands(t_excmd *cmd1, t_excmd *cmd2)
{
	cmd1->next = cmd2;
	cmd2->prev = cmd1;
}
