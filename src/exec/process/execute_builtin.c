#include "minishell.h"

t_bool	execute_builtin(t_child_behavior_params p)
{
	if (p.cmd->in_a_child)
		return (*p.cmd->proto)(p.cmd);
	else
	{
		p.params->status = (*p.cmd->proto)(p.cmd);
		if (restore_std(p.in_dup, p.out_dup) == false)
			return (1);
		return (p.params->status);
	}
}
