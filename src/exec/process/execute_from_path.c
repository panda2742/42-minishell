/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_from_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:59:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/09 14:32:02 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_print_err(t_excmd *cmd);

void	execute_from_path(t_excmd *cmd)
{
	int			i;
	t_env_var	*path_var;
	char		*fullpath;

	if (cmd->name && ft_strchr(cmd->name, '/') == NULL)
	{
		path_var = get_var(&cmd->vars->minishell->env, "PATH");
		if (path_var != NULL)
		{
			cmd->paths = ft_split(path_var->value, ":");
			if (cmd->paths == NULL)
				cmd->paths = empty_tab();
		}
		else
			cmd->paths = empty_paths();
		i = 0;
		while (cmd->paths[i])
		{
			fullpath = get_full_path(cmd->paths[i], cmd->name);
			i++;
			if (access(fullpath, F_OK) != 0)
			{
				cmd->vars->errs.exc_access_fok = 1;
				free(fullpath);
				continue ;
			}
			if (access(fullpath, X_OK) != 0)
			{
				cmd->vars->errs.exc_access_xok = 1;
				free(fullpath);
				continue ;
			}
			if (execve(fullpath, cmd->argv, cmd->envp) == -1)
			{
				cmd->vars->errs.exc_execve = 1;
				free(fullpath);
				break ;
			}
			free(fullpath);
		}
	}
	else if (cmd->name && ft_strchr(cmd->name, '/'))
	{
		if (access(cmd->name, F_OK) != 0)
			cmd->vars->errs.exc_access_fok = 1;
		else if (access(cmd->name, X_OK) != 0)
			cmd->vars->errs.exc_access_xok = 1;
		else if (execve(cmd->name, cmd->argv, cmd->envp) == -1)
			cmd->vars->errs.exc_execve = 1;
	}
	else
	{
		cmd->vars->errs.exc_access_fok = 1;
	}
	_print_err(cmd);
}

static void	_print_err(t_excmd *cmd)
{
	if (cmd->vars->errs.exc_access_xok)
	{
		puterr(ft_sprintf(": %s: Permission denied\n", cmd->name), false);
		cmd->vars->status = EXIT_CANNOT_EXEC;
	}
	else if (cmd->vars->errs.exc_access_fok)
	{
		puterr(ft_sprintf(": %s: Command not found\n", cmd->name), false);
		cmd->vars->status = EXIT_NOT_FOUND;
	}
	else if (cmd->vars->errs.exc_execve)
	{
		cmd->vars->status = EXIT_FAILURE;
		puterr(ft_sprintf(": %s", cmd->name), true);
	}
}
