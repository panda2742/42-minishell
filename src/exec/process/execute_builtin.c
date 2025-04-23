#include "minishell.h"

t_bool	execute_builtin(t_child_behavior_params p)
{
	int	status;

	if (p.cmd->in_a_child)
	{
		status = (*p.cmd->proto)(p.cmd);
		sclose_fd(p.cmd->in_redirects.final_fd.fd, NULL);
		sclose_fd(p.cmd->out_redirects.final_fd.fd, NULL);
		sclose_fd(p.cmd->pipe[0], &p.cmd->pipe_open[1]);
		free_env(p.cmd->env);
		ft_free_strtab(p.cmd->envp);
		free_cmds(p.params->cmds);
		exit(status);
	}
	else
	{
		p.params->status = (*p.cmd->proto)(p.cmd);
		if (restore_std(p.in_dup, p.out_dup) == false)
			return (1);
		return (p.params->status);
	}
}
