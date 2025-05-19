/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_commands_utils2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:24:04 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/19 10:25:46 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	_create_pipe_if_necessary(t_excmd *cmd)
{
	if (cmd->id < cmd->vars->nb_cmd)
	{
		if (pipe(cmd->pipe) == -1)
		{
			puterr(ft_sprintf(": Pipe creation failed"), true);
			return (true);
		}
		cmd->pipe_open[0] = true;
		cmd->pipe_open[1] = true;
	}
	return (false);
}

void	_child_life(t_execvars *vars, t_excmd *cmd)
{
	int		status;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	status = _setup_cmd(cmd);
	close_pipe(cmd, 3);
	if (cmd->prev)
		close_pipe(cmd->prev, 1);
	if (status != EXIT_SUCCESS)
		_free_everything(cmd, vars, status, false);
	if (cmd->proto == NULL)
	{
		execute_from_path(cmd,
			cmd->in_redirects.size + cmd->out_redirects.size);
		_free_everything(cmd, vars, vars->status, true);
	}
	else
		_free_everything(cmd, vars, cmd->proto(cmd), true);
}

t_bool	_error_or_parent_life(int fork_id, t_execvars *vars,
					t_excmd *cmd, pid_t *last_fork)
{
	if (fork_id < 0)
	{
		vars->status = EXIT_FORK_FAILED;
		puterr(ft_sprintf(": Pipeline stopped; %d failed", fork_id), true);
		close_pipe(cmd, 3);
		return (true);
	}
	close_pipe(cmd, 2);
	if (cmd->prev)
		close_pipe(cmd->prev, 1);
	if (cmd->next == NULL)
		*last_fork = fork_id;
	vars->nb_launched++;
	return (false);
}

void	_trigger_waits(t_execvars *vars, pid_t last_fork)
{
	int		wait_status;
	int		sig;
	pid_t	ended_pid;

	while (vars->nb_launched)
	{
		ended_pid = waitpid(-1, &wait_status, 0);
		if (ended_pid == last_fork)
		{
			if (WIFEXITED(wait_status))
				vars->status = WEXITSTATUS(wait_status);
			else if (WIFSIGNALED(wait_status))
			{
				sig = WTERMSIG(wait_status);
				if (sig == SIGINT)
					vars->status = 128 + SIGINT;
				else if (sig == SIGQUIT)
					(write(1, "Quit (core dumped)", 19),
						vars->status = 128 + SIGQUIT);
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		vars->nb_launched--;
	}
}

void	exec_multiple_commands(t_execvars *vars)
{
	t_excmd	*cmd;
	pid_t	fork_id;
	pid_t	last_fork;

	cmd = *vars->cmds;
	while (cmd)
	{
		if (_create_pipe_if_necessary(cmd))
			break ;
		fork_id = fork();
		if (fork_id == 0)
			_child_life(vars, cmd);
		if (_error_or_parent_life(fork_id, vars, cmd, &last_fork))
			break ;
		cmd = cmd->next;
	}
	signal(SIGINT, SIG_IGN);
	_trigger_waits(vars, last_fork);
	clear_every_tmpfile(vars->cmds);
}
