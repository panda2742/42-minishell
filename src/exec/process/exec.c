/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:57:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/22 18:39:54 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned char	_init_child_behavior(t_child_behavior_params p);

t_execparams	exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_excmd			*cmd;
	t_execparams	params;
	t_streamfd		std_dup[2];
	unsigned char	init_behavior_res;

	if (load_pipeline_params(minishell, &params, cmds) == false)
		return (params);
	cmd = *cmds;
	while (cmd)
	{
		std_dup[0].fd = -1;
		std_dup[1].fd = -1;
		std_dup[0].type = STREAM_STD;
		std_dup[1].type = STREAM_STD;
		cmd->minishell = minishell;
		cmd->params = &params;
		init_behavior_res = _init_child_behavior((t_child_behavior_params){
			.minishell=minishell,.cmd=cmd,.in_dup=&std_dup[0],
			.out_dup=&std_dup[1],.params=&params});
		if (init_behavior_res == 0)
			break ;
		if (init_behavior_res == 1)
		{
			cmd = cmd->next;
			continue ;
		}
		if (cmd->proto == NULL)
			execute_from_path(minishell, &params, cmd);
		else
			execute_builtin((t_child_behavior_params){
				.minishell=minishell,.cmd=cmd,.in_dup=&std_dup[0],
				.out_dup=&std_dup[1],.params=&params});
		if (params.status == -2)
			return (params);
		if (cmd->in_a_child)
		{
			sclose_fd(cmd->in_redirects.final_fd.fd, NULL);
			sclose_fd(cmd->out_redirects.final_fd.fd, NULL);
			free_env(cmd->env);
			ft_free_strtab(cmd->envp);
			free_cmds(cmds);
			exit(0);
		}
		break ;
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

static unsigned char	_init_child_behavior(t_child_behavior_params p)
{
	p.cmd->envp = p.minishell->env.envlst;
	p.cmd->in_dup = p.in_dup;
	p.cmd->out_dup = p.out_dup;
	if (create_cmd_pipe(p.cmd, p.params) == false)
	{
		if (p.params->errs.exc_pipe)
			return (0);
		return (1);
	}
	if (!p.cmd->name)
		return (1);
	p.params->nb_launched++;
	if (create_child(p.cmd, p.params) == false)
	{
		if (p.params->errs.exc_fork == 1)
			return (0);
		return (1);
	}
	if (create_streams(p.cmd, p.params, p.in_dup, p.out_dup) == false)
		return (1); 
	return (2);
}
