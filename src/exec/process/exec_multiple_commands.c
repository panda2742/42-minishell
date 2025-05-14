/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:24:04 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 16:59:53 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_setup_cmd(t_excmd *cmd);
static int	_check_input_redir(t_excmd *cmd);
static int	_check_output_redir(t_excmd *cmd);
static int	_create_input_dup2_redir(t_excmd *cmd);
static int	_create_output_dup2_redir(t_excmd *cmd);

static void	_free_everything(t_excmd *cmd, t_execvars *vars, int status,
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

static t_bool	_create_pipe_if_necessary(t_excmd *cmd)
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

static void	_child_life(t_execvars *vars, t_excmd *cmd)
{
	int		status;

	signal(SIGQUIT, SIG_DFL);
	status = _setup_cmd(cmd);
	close_pipe(cmd, 3);
	if (cmd->prev)
		close_pipe(cmd->prev, 1);
	if (status != EXIT_SUCCESS)
		_free_everything(cmd, vars, status, false);
	if (cmd->proto == NULL)
	{
		execute_from_path(cmd);
		_free_everything(cmd, vars, vars->status, true);
	}
	else
		_free_everything(cmd, vars, cmd->proto(cmd), true);
}

static t_bool	_error_or_parent_life(int fork_id, t_execvars *vars,
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

static void	_trigger_waits(t_execvars *vars, pid_t last_fork)
{
	int		wait_status;
	pid_t	ended_pid;

	while (vars->nb_launched)
	{
		ended_pid = waitpid(-1, &wait_status, 0);
		if (ended_pid == last_fork)
		{
			if (WIFEXITED(wait_status))
				vars->status = WEXITSTATUS(wait_status);
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
	_trigger_waits(vars, last_fork);
	clear_every_tmpfile(vars->cmds);
}

static int	_setup_cmd(t_excmd *cmd)
{
	if (_check_input_redir(cmd) == EXIT_FAILURE)
		return (cmd->vars->status);
	if (_check_output_redir(cmd) == EXIT_FAILURE)
		return (cmd->vars->status);
	if (_create_input_dup2_redir(cmd) == EXIT_FAILURE)
	{
		close_pipe(cmd, 3);
		return (cmd->vars->status);
	}
	if (_create_output_dup2_redir(cmd) == EXIT_FAILURE)
	{
		close_pipe(cmd, 3);
		return (cmd->vars->status);
	}
	close_pipe(cmd, 3);
	return (EXIT_SUCCESS);
}

static int	_check_input_redir(t_excmd *cmd)
{
	if (cmd->in_redirects.size > 0
		&& get_last_redirect(&cmd->in_redirects) == NULL)
	{
		cmd->vars->status = EXIT_FAILURE;
		return (cmd->vars->status);
	}
	else if (cmd->in_redirects.size == 0 && cmd->id > 1)
	{
		if (cmd->prev)
			cmd->in_redirects.final_fd.fd = cmd->prev->pipe[0];
		cmd->in_redirects.final_fd.type = STREAM_PIPE;
	}
	return (cmd->vars->status);
}

static int	_check_output_redir(t_excmd *cmd)
{
	if (cmd->out_redirects.size > 0
		&& get_last_redirect(&cmd->out_redirects) == NULL)
	{
		if (cmd->in_redirects.size > 0
			&& cmd->in_redirects.final_fd.type == STREAM_REDIR)
			close(cmd->in_redirects.final_fd.fd);
		cmd->vars->status = EXIT_FAILURE;
		return (cmd->vars->status);
	}
	else if (cmd->out_redirects.size == 0 && cmd->id < cmd->vars->nb_cmd)
	{
		cmd->out_redirects.final_fd.fd = cmd->pipe[1];
		cmd->out_redirects.final_fd.type = STREAM_PIPE;
	}
	return (cmd->vars->status);
}

static int	_create_input_dup2_redir(t_excmd *cmd)
{
	if (cmd->in_redirects.final_fd.type != STREAM_STD)
	{
		if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
		{
			puterr(ft_sprintf(": %s(%d) dup2 input error", cmd->name, cmd->id),
				true);
			if (cmd->in_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->in_redirects.final_fd.fd);
			if (cmd->out_redirects.size > 0
				&& cmd->out_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			if (cmd->in_redirects.final_fd.type == STREAM_REDIR
				&& cmd->in_redirects.last->is_heredoc == true)
				unlink(cmd->in_redirects.last->filepath);
			return (cmd->vars->status);
		}
		if (cmd->in_redirects.final_fd.type == STREAM_REDIR
			&& cmd->in_redirects.final_fd.fd > STDERR_FILENO)
			close(cmd->in_redirects.final_fd.fd);
	}
	return (cmd->vars->status);
}

static int	_create_output_dup2_redir(t_excmd *cmd)
{
	if (cmd->out_redirects.final_fd.type != STREAM_STD)
	{
		if (dup2(cmd->out_redirects.final_fd.fd, STDOUT_FILENO) == -1)
		{
			puterr(ft_sprintf(": %s(%d) dup2 output error", cmd->name, cmd->id),
				true);
			if (cmd->out_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return (cmd->vars->status);
		}
		if (cmd->out_redirects.final_fd.type == STREAM_REDIR)
			close(cmd->out_redirects.final_fd.fd);
	}
	return (cmd->vars->status);
}
