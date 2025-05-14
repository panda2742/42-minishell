/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_execvars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:18:16 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/14 14:23:30 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_set_args_to_zero(t_execvars *vars)
{
	vars->nb_launched = 0;
	vars->status = EXIT_SUCCESS;
	vars->errs.errors_raw = 0;
}

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
			cmd->id = vars->nb_cmd;
			if (cmd->name)
				cmd->proto = load_builtin(cmd->name, &cmd->proto);
			cmd = cmd->next;
		}
	}
	_set_args_to_zero(vars);
	vars->minishell = minishell;
	return (vars);
}

void	reset_execvars(t_execvars *vars)
{
	vars->errs.errors_raw = 0;
	vars->status = EXIT_SUCCESS;
}
