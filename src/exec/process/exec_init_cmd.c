/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:56:24 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/15 15:41:26 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_init_cmd_redirects(t_excmd *cmd);

t_bool	exec_init_cmd(t_excmd *cmd, t_execparams *params)
{
	if (cmd->proto != NULL && params->nb_cmd == 1)
		cmd->in_a_child = false;
	if (cmd->next)
	{
		cmd->pipe_open[0] = true;
		cmd->pipe_open[1] = true;
		pipe(cmd->pipe);
	}
	return (_init_cmd_redirects(cmd));
}

static t_bool	_init_cmd_redirects(t_excmd *cmd)
{
	const t_redir_manager	*in = &cmd->in_redirects;
	const t_redir_manager	*out = &cmd->out_redirects;

	if (get_last_redirect((t_redir_manager *)in) == NULL && in->size > 0)
	{
		if (in->problematic && in->problematic->filepath)
			puterr(ft_sprintf(": %s", in->problematic->filepath), true);
		else
			puterr(ft_sprintf(": input redirecting"), true);
		return (false);
	}
	if (get_last_redirect((t_redir_manager *)out) == NULL && out->size > 0)
	{
		if (out->problematic && out->problematic->filepath)
			puterr(ft_sprintf(": %s", out->problematic->filepath), true);
		else
			puterr(ft_sprintf(": output redirecting"), true);
		return (false);
	}
	return (true);
}
