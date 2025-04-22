/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:59:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/21 14:14:57 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_print_err(t_execparams *params, t_excmd *cmd);

t_bool	execute_from_path(t_minishell *minishell, t_execparams *params,
			t_excmd *cmd)
{
	int			i;
	t_env_var	*path_var;
	char		*fullpath;

	path_var = get_var(&minishell->env, "PATH");
	if (path_var != NULL)
	{
		cmd->paths = ft_split(path_var->value, ":");
		if (cmd->paths == NULL)
			cmd->paths = empty_tab();
	}
	else
		cmd->paths = empty_tab();
	i = 0;
	while (cmd->paths[i])
	{
		fullpath = get_full_path(cmd->paths[i], cmd->name);
		i++;
		if (access(fullpath, F_OK) != 0)
		{
			params->errs.exc_access_fok = 1;
			free(fullpath);
			continue ;
		}
		if (access(fullpath, X_OK) != 0)
		{
			params->errs.exc_access_xok = 1;
			free(fullpath);
			continue ;
		}
		if (execve(fullpath, cmd->argv, cmd->envp) == -1)
		{
			params->errs.exc_execve = 1;
			free(fullpath);
			break ;
		}
	}
	if (access(cmd->name, F_OK) != 0)
		params->errs.exc_access_fok = 1;
	else if (access(fullpath, X_OK) != 0)
		params->errs.exc_access_xok = 1;
	else if (execve(fullpath, cmd->argv, cmd->envp) == -1)
		params->errs.exc_execve = 1;
	_print_err(params, cmd);
	return (false);
}

static void	_print_err(t_execparams *params, t_excmd *cmd)
{
	if (params->errs.exc_access_xok)
		puterr(ft_sprintf(": %s: Permission denied\n", cmd->name), false);
	else if (params->errs.exc_access_fok)
		puterr(ft_sprintf(": %s: Command not found\n", cmd->name), false);
	else if (params->errs.exc_execve)
		puterr(ft_sprintf(": %s", cmd->name), true);
}
