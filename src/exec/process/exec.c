/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:57:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/11 12:13:02 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_load_env_strlst(t_execvars *vars);

t_execvars	*exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_execvars		*vars;

	vars = create_execvars(minishell, cmds);
	if (vars == NULL)
	{
		puterr(ft_sprintf(": error:  Memory allocation error\n"), false);
		return (NULL);
	}
	if (vars->nb_cmd == 0)
		return (vars);
	if (_load_env_strlst(vars) == false)
		return (vars);
	if (vars->nb_cmd == 1 && (*vars->cmds)->proto != NULL)
		exec_single_builtin(*(vars->cmds));
	else
		exec_multiple_commands(vars);
	free_cmds(vars->cmds);
	ft_free_strtab(minishell->env.envlst);
	return (vars);
}

static t_bool	_load_env_strlst(t_execvars *vars)
{
	t_excmd	*cmd;

	vars->minishell->env.envlst = env_to_strlst(&vars->minishell->env);
	if (vars->minishell->env.envlst == NULL)
	{
		vars->errs.exc_env_strlst = 1;
		free(vars->cmds);
		puterr(ft_sprintf(
				": error: Pipeline init failure (memory allocation),\
					killing %s\n" PROJECT_NAME), false);
		return (false);
	}
	cmd = *vars->cmds;
	while (cmd)
	{
		cmd->envp = vars->minishell->env.envlst;
		cmd = cmd->next;
	}
	return (true);
}
