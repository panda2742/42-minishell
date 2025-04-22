#include "minishell.h"

static void		_set_final_fd(t_excmd *cmd);
static t_bool	_init_stdin_dup(t_excmd *cmd, t_execparams *params,
					t_streamfd *in_dup);
static t_bool	_init_stdout_dup(t_excmd *cmd, t_execparams *params,
					t_streamfd *out_dup);

t_bool	create_streams(t_excmd *cmd, t_execparams *params, t_streamfd *in_dup,
			t_streamfd *out_dup)
{
	t_bool	dup_results[2];

	_set_final_fd(cmd);
	dup_results[0] = _init_stdin_dup(cmd, params, in_dup);
	dup_results[1] = _init_stdout_dup(cmd, params, out_dup);
	if (cmd->prev)
		sclose_fd(cmd->prev->pipe[0], &cmd->prev->pipe_open[0]);
	if (cmd->next)
		sclose_fd(cmd->pipe[1], &cmd->pipe_open[1]);
	if ((dup_results[0] & dup_results[1]) == 0)
		free_cmds(params->cmds);
	return (dup_results[0] & dup_results[1]);
}

static void	_set_final_fd(t_excmd *cmd)
{
	if (cmd->in_redirects.final_fd.type == STREAM_STD)
		cmd->in_redirects.final_fd.fd = STDIN_FILENO;
	if (cmd->out_redirects.final_fd.type == STREAM_STD)
		cmd->out_redirects.final_fd.fd = STDOUT_FILENO;
	if (cmd->in_redirects.final_fd.type == STREAM_PIPE)
		cmd->in_redirects.final_fd.fd = cmd->prev->pipe[0];
	if (cmd->out_redirects.final_fd.type == STREAM_PIPE)
		cmd->out_redirects.final_fd.fd = cmd->pipe[1];
}

static t_bool	_init_stdin_dup(t_excmd *cmd, t_execparams *params,
					t_streamfd *in_dup)
{
	if (cmd->in_redirects.final_fd.type == STREAM_STD)
		return (true);
	if (in_dup && cmd->in_a_child == false)
	{
		in_dup->fd = dup(STDIN_FILENO);
		if (in_dup->fd == -1)
		{
			params->errs.exc_dup_in = 1;
			sclose_fd(cmd->in_redirects.final_fd.fd, NULL);
			puterr(ft_sprintf(": dup STDIN error"), true);
			return (false);
		}
		in_dup->type = STREAM_STD;
	}
	if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
	{
		params->errs.exc_dup2_in = 1;
		sclose_fd(cmd->in_redirects.final_fd.fd, NULL);
		puterr(ft_sprintf(": dup2 input error"), true);
		return (false);
	}
	sclose_fd(cmd->in_redirects.final_fd.fd, NULL);
	return (true);
}

static t_bool	_init_stdout_dup(t_excmd *cmd, t_execparams *params, t_streamfd *out_dup)
{
	if (cmd->out_redirects.final_fd.type == STREAM_STD)
		return (true);
	if (out_dup && cmd->in_a_child == false)
	{
		out_dup->fd = dup(STDOUT_FILENO);
		if (out_dup->fd == -1)
		{
			params->errs.exc_dup_in = 1;
			sclose_fd(cmd->out_redirects.final_fd.fd, NULL);
			puterr(ft_sprintf(": dup STDOUT error"), true);
			return (false);
		}
		out_dup->type = STREAM_STD;
	}
	if (dup2(cmd->out_redirects.final_fd.fd, STDOUT_FILENO) == -1)
	{
		params->errs.exc_dup2_out = 1;
		sclose_fd(cmd->out_redirects.final_fd.fd, NULL);
		puterr(ft_sprintf(": dup2 output error"), true);
		return (false);
	}
	sclose_fd(cmd->out_redirects.final_fd.fd, NULL);
	return (true);
}
