/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:43 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 15:31:23 by abonifac         ###   ########.fr       */
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
			return (free_res_return_null(res));
	}
	res->in_a_child = true;
	res->proto = NULL;
	res->argc = 0;
	res->argv = empty_tab();
	res->env = env;
	res->envp = empty_tab();
	res->paths = empty_tab();
	_init_redirects(res);
	res->vars = NULL;
	res->prev = NULL;
	res->next = NULL;
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
	cmd->std_dup[0].fd = -1;
	cmd->std_dup[1].fd = -1;
	cmd->std_dup[0].type = STREAM_STD;
	cmd->std_dup[1].type = STREAM_STD;
}

// Je n ai pas tout compris a ce qu il se passe ici
t_redir	*add_redirect(t_excmd *cmd, t_redir_type type, t_redir *redirect)
{
	t_redir_manager	*manager;
	t_redir			*last;

	if (!redirect)
		return (NULL);
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
			return (free_redir_and_return_null(redirect));
		manager->redirects[0] = redirect;
		manager->size += 1;
		return (redirect);
	}
	last = *manager->redirects;
	update_last_next(&last, redirect);
	manager->size += 1;
	return (redirect);
}
