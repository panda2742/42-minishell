#include "minishell.h"

t_bool	create_child(t_excmd *cmd, t_execparams *params)
{
	pid_t	forkid;

	if (!cmd->in_a_child)
		return (true);
	forkid = fork();
	if (forkid == 0)
		return (true);
	sclose_fd(cmd->pipe[1], &cmd->pipe_open[1]);
	if (forkid > 0)
		return (false);
	if (forkid < 0)
	{
		params->nb_launched--;
		params->errs.exc_fork = 1;
		free_cmds(params->cmds);
		puterr(ft_sprintf(": fork error"), true);
		return (false);
	}
	return (true);
}
