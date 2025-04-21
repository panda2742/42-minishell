/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:57:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/21 17:55:01 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execparams	exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_excmd			*cmd;
	t_execparams	params;
	t_streamfd		std_dup[2];

	if (load_pipeline_params(minishell, &params, cmds) == false)
		return (params);
	cmd = *cmds;
	while (cmd)
	{
		cmd->envp = minishell->env.envlst;
		if (create_cmd_pipe(cmd, &params) == false)
		{
			if (params.errs.exc_pipe)
				break ;
			cmd = cmd->next;
			continue ;
		}
		params.nb_launched++;
		if (create_child(cmd, &params) == false)
		{
			if (params.errs.exc_fork == 1)
				break ;
			cmd = cmd->next;
			continue ;
		}
		if (create_streams(cmd, &std_dup[0], &std_dup[1]) == false)
			exit(0);
		if (cmd->proto == NULL)
			execute_from_path(minishell, cmd);
		else
		{
			(*cmd->proto)(cmd);
			if (cmd->in_a_child)
			{
				if (std_dup[0].type == STREAM_STD)
					close(std_dup[0].fd);
				if (std_dup[1].type == STREAM_STD)
					close(std_dup[1].fd);
				exit(0);
			}
			else
			{
				if (std_dup[0].type == STREAM_STD && dup2(std_dup[0].fd, STDIN_FILENO) == -1)
				{
					puterr(ft_sprintf(": dup2 input reset error"), true);
					if (std_dup[1].type == STREAM_STD && dup2(std_dup[1].fd, STDOUT_FILENO) == -1)
					{
						puterr(ft_sprintf(": dup2 output reset error"), true);
						close(std_dup[1].fd);
					}
					close(std_dup[0].fd);
					return (params);
				}
				if (std_dup[1].type == STREAM_STD && dup2(std_dup[1].fd, STDOUT_FILENO) == -1)
				{
					puterr(ft_sprintf(": dup2 output reset error"), true);
					close(std_dup[1].fd);
				}
			}
		}
		if (cmd->in_a_child && cmd->proto == NULL)
		{
			free_env(cmd->env);
			ft_free_strtab(cmd->envp);
			free_cmds(cmds);
			exit(0);
		}
		cmd = cmd->next;
	}
	cmd = *cmds;
	while (params.nb_launched)
	{
		if (cmd->prev)
			waitpid(-1, NULL, 0);
		else
			waitpid(-1, &minishell->last_status, 0);
		params.nb_launched--;
		cmd = cmd->next;
	}
	ft_free_strtab(minishell->env.envlst);
	return (params);
}
