/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:59:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/17 11:46:26 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	create_streams(t_excmd *cmd)
{
	if (cmd->in_redirects.final_fd.fd == STDIN_FILENO)
		cmd->in_redirects.final_fd.type = STREAM_STD;
	if (cmd->out_redirects.final_fd.fd == STDOUT_FILENO)
		cmd->out_redirects.final_fd.type = STREAM_STD;
	if (cmd->prev && cmd->in_redirects.size == 0)
	{
		cmd->in_redirects.final_fd.fd = cmd->prev->pipe[0];
		cmd->in_redirects.final_fd.type = STREAM_PIPE;
	}
	if (cmd->next && cmd->out_redirects.size == 0)
	{
		cmd->out_redirects.final_fd.fd = cmd->pipe[1];
		cmd->out_redirects.final_fd.type = STREAM_PIPE;
	}
	if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
	{
		puterr(ft_sprintf(": dup2 in-stream error"), true);
		return (false);
	}
	if (dup2(cmd->in_redirects.final_fd.fd, STDOUT_FILENO) == -1)
	{
		puterr(ft_sprintf(": dup2 out-stream error"), true);
		return (false);
	}
	if (cmd->prev)
		close_pipe(cmd->prev->pipe[0], &cmd->pipe_open[0]);
	if (cmd->next)
		close_pipe(cmd->pipe[1], &cmd->pipe_open[1]);
	return (true);
}

t_bool	execute_from_path(t_minishell *minishell, t_excmd *cmd, t_excmd **cmds)
{
	int			i;
	t_env_var	*path_var;
	char		*fullpath;

	path_var = get_var(&minishell->env, "PATH");
	if (path_var != NULL)
		cmd->paths = ft_split(path_var->value, ":");
	else
		cmd->paths = empty_tab();
	i = 0;
	while (cmd->paths[i])
	{
		fullpath = get_full_path(cmd->paths[i], cmd->name);
		i++;
		if (access(fullpath, F_OK | X_OK) != 0)
			continue ;
		if (execve(fullpath, cmd->argv, cmd->envp) == -1)
			break ;
	}
	if (access(cmd->name, F_OK | X_OK) == 0)
		execve(cmd->name, cmd->argv, cmd->envp);
	if (dup2(STDOUT_FILENO, cmd->in_redirects.final_fd.fd) == -1)
	{
		puterr(ft_sprintf(": dup2 in-stream error"), true);
		return (false);
	}
	if (dup2(STDOUT_FILENO, cmd->out_redirects.final_fd.fd) == -1)
	{
		puterr(ft_sprintf(": dup2 out-stream error"), true);
		return (false);
	}
	free_env(cmd->env);
	ft_free_strtab(cmd->envp);
	free_cmds(cmds);
	puterr(ft_sprintf(": %s", cmd->name), true);
	return (false);
}
