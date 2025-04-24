#include "minishell.h"

t_execvars	*create_execvars(t_minishell *minishell, t_excmd **cmds)
{
	t_execvars	*vars;
	t_excmd		*cmd;

	vars = ft_memalloc(sizeof(t_execvars));
	if (vars == NULL)
		return (NULL);
	vars->nb_cmd = 0;
	vars->cmds = cmds;
	if (cmds)
	{
		cmd = *cmds;
		while (cmd)
		{
			vars->nb_cmd++;
			cmd->vars = vars;
			if (cmd->name)
				cmd->proto = load_builtin(cmd->name, &cmd->proto);
			cmd = cmd->next;
		}
	}
	vars->nb_launched = 0;
	vars->status = EXIT_SUCCESS;
	vars->errs.errors_raw = 0;
	vars->minishell = minishell;
	return (vars);
}

void	reset_execvars(t_execvars *vars)
{
	vars->errs.errors_raw = 0;
	vars->status = EXIT_SUCCESS;
}
