#include "minishell.h"

static t_bool	_manage_redirects(t_excmd *cmd, t_execparams *params);
static t_bool	_load_redirects(t_redir_manager *manager);
static void		_set_default_fds(t_excmd *cmd);

t_bool	create_cmd_pipe(t_excmd *cmd, t_execparams *params)
{
	if (cmd->proto != NULL && params->nb_cmd == 1)
		cmd->in_a_child = false;
	else
		cmd->in_a_child = true;
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
		{
			params->errs.exc_pipe = 1;
			free_cmds(params->cmds);
			puterr(ft_sprintf(
				": error: Pipe creation failure"
				), true);
			return (false);
		}
		cmd->pipe_open[0] = true;
		cmd->pipe_open[1] = true;
	}
	return (_manage_redirects(cmd, params));
}

static t_bool	_manage_redirects(t_excmd *cmd, t_execparams *params)
{
	_set_default_fds(cmd);
	if (_load_redirects(&cmd->in_redirects) == false)
	{
		free_cmds(params->cmds);
		return (false);
	}
	if (_load_redirects(&cmd->out_redirects) == false)
	{
		if (cmd->in_redirects.final_fd.fd == STREAM_REDIR)
			close(cmd->in_redirects.final_fd.fd);
		free_cmds(params->cmds);
		return (false);
	}
	return (true);
}

static t_bool	_load_redirects(t_redir_manager *manager)
{
	if (get_last_redirect(manager) == NULL && manager->size > 0)
	{
		if (manager->problematic && manager->problematic->filepath)
			puterr(ft_sprintf(": %s", manager->problematic->filepath), true);
		else
		{
			if (manager->type == IN_REDIR)
				puterr(ft_sprintf(": input redirecting"), true);
			else
				puterr(ft_sprintf(": output redirecting"), true);
		}
		return (false);
	}
	return (true);
}

static void	_set_default_fds(t_excmd *cmd)
{
	if (cmd->prev)
		cmd->in_redirects.final_fd.type = STREAM_PIPE;
	if (cmd->next)
		cmd->out_redirects.final_fd.type = STREAM_PIPE;
}
