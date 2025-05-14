/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_commands_utils1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:24:04 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 17:05:00 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_free_everything(t_excmd *cmd, t_execvars *vars, int status,
				t_bool unlink_tmp)
{
	if (unlink_tmp)
	{
		if (cmd->in_redirects.final_fd.type == STREAM_REDIR
			&& cmd->in_redirects.last->is_heredoc == true)
			unlink(cmd->in_redirects.last->filepath);
	}
	ft_free_strtab(cmd->vars->minishell->env.envlst);
	free_env(&cmd->vars->minishell->env);
	free_cmds(vars->cmds);
	free(vars);
	exit(status);
}
