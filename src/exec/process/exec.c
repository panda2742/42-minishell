/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:57:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 11:19:34 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_load_env_strlst(t_execvars *vars);
static t_exit	_read_heredocs(t_redir_manager *redirects_manager);

t_execvars	*exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_execvars		*vars;
	t_excmd			*cmd;
	int				ttyfd;

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
	cmd = *cmds;
	while (cmd)
	{
		if (cmd->in_redirects.size && _read_heredocs(&cmd->in_redirects) == EXIT_FAILURE)
		{
			clear_every_tmpfile(cmds);
			puterr(ft_sprintf(": heredoc error.\n"), false);
			vars->status = 1;
			return (vars);
		}
		cmd = cmd->next;
	}
	if (last_signal == 5)
	{
		ttyfd = open("/dev/tty", O_RDWR);
		if (ttyfd > STDERR_FILENO)
		{
			dup2(ttyfd, STDIN_FILENO);
			close(ttyfd);
		}
		last_signal = 0;
		vars->status = 130;
	}
	if (vars->nb_cmd == 1 && (*vars->cmds)->proto != NULL)
		exec_single_builtin(*(vars->cmds));
	else
		exec_multiple_commands(vars);
	free_cmds(vars->cmds);
	ft_free_strtab(minishell->env.envlst);
	return (vars);
}

static t_exit	_read_heredocs(t_redir_manager *redirects_manager)
{
	t_redir	*elt;
	size_t	nb_heredoc;
	t_exit	heredoc_status;

	nb_heredoc = -1;
	elt = *redirects_manager->redirects;
	while (elt)
	{
		if (elt->is_heredoc)
		{
			nb_heredoc++;
			elt->heredoc_id = nb_heredoc;
		}
		elt = elt->next;
	}
	elt = *redirects_manager->redirects;
	while (elt)
	{
		if (elt->is_heredoc)
		{
			heredoc_status = heredoc(
				elt->heredoc_del,
				&elt->filepath,
				elt->heredoc_id != nb_heredoc && elt->next == NULL);
			if (heredoc_status == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		elt = elt->next;
	}
	return (EXIT_SUCCESS);
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
