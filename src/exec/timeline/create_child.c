#include "minishell.h"

t_bool	create_child(t_excmd *cmd, t_execparams *params, size_t *proc)
{
	pid_t	forkid;

	if (!cmd->in_a_child)
		return (true);
	forkid = fork();
	if (forkid == 0)
		return (true);
	if (forkid > 0)
	{
		if (cmd->prev)
			sclose_fd(cmd->prev->pipe[0], &cmd->prev->pipe_open[0]);
		if (cmd->next)
			sclose_fd(cmd->pipe[1], &cmd->pipe_open[1]);
		return (false);
	}
	if (forkid < 0)
	{
		(*proc)--;
		params->errs.exc_fork = 1;
		free_cmds(params->cmds);
		puterr(ft_sprintf(": fork error"), true);
		return (false);
	}
	return (true);
}
