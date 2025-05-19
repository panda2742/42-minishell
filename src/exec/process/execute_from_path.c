/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_from_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:59:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/19 10:24:43 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_print_err(t_excmd *cmd);

static void	_execute_with_name(t_excmd *cmd)
{
	DIR			*dir;

	dir = opendir(cmd->name);
	if (dir)
	{
		closedir(dir);
		cmd->vars->errs.exc_directory = 1;
	}
	else
	{
		if (access(cmd->name, F_OK) != 0)
			cmd->vars->errs.exc_access_fok = 1;
		else if (access(cmd->name, X_OK) != 0)
			cmd->vars->errs.exc_access_xok = 1;
		else if (execve(cmd->name, cmd->argv, cmd->envp) == -1)
			cmd->vars->errs.exc_execve = 1;
	}
}

static t_bool	_test_path(t_excmd *cmd, char *path)
{
	char	*fullpath;

	fullpath = get_full_path(path, cmd->name);
	if (access(fullpath, F_OK) != 0)
	{
		cmd->vars->errs.exc_access_fok = 1;
		free(fullpath);
		return (false);
	}
	if (access(fullpath, X_OK) != 0)
	{
		cmd->vars->errs.exc_access_xok = 1;
		free(fullpath);
		return (false);
	}
	if (execve(fullpath, cmd->argv, cmd->envp) == -1)
	{
		cmd->vars->errs.exc_execve = 1;
		free(fullpath);
		return (true);
	}
	free(fullpath);
	return (false);
}

static char	**_get_paths(t_excmd *cmd, t_env_var *path_var)
{
	cmd->paths = ft_split(path_var->value, ":");
	if (cmd->paths == NULL)
		cmd->paths = empty_paths();
	if (cmd->paths[0] == NULL)
	{
		free(cmd->paths);
		cmd->paths = empty_paths();
	}
	return (cmd->paths);
}

void	execute_from_path(t_excmd *cmd, size_t redir_size)
{
	int			i;
	t_env_var	*path_var;

	if (cmd->name)
	{
		if (ft_strchr(cmd->name, '/') == NULL)
		{
			path_var = get_var(&cmd->vars->minishell->env, "PATH");
			if (path_var != NULL)
				cmd->paths = _get_paths(cmd, path_var);
			else
				cmd->paths = empty_paths();
			i = 0;
			while (cmd->paths[i])
			{
				if (_test_path(cmd, cmd->paths[i++]) == true)
					break ;
			}
		}
		else
			_execute_with_name(cmd);
	}
	else
		cmd->vars->errs.exc_access_fok = redir_size == 0;
	_print_err(cmd);
}

static void	_print_err(t_excmd *cmd)
{
	if (cmd->vars->errs.exc_directory)
	{
		puterr(ft_sprintf(": %s: Is a directory\n", cmd->name), false);
		cmd->vars->status = EXIT_CANNOT_EXEC;
	}
	else if (cmd->vars->errs.exc_access_xok)
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
