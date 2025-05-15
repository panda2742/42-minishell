/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:57:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/15 14:41:11 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exit	_read_heredocs(t_redir_manager *redirects_manager);

static t_bool	_handle_signal(void)
{
	int	ttyfd;

	if (g_last_signal == SIG_HEREDOC)
	{
		ttyfd = open("/dev/tty", O_RDWR);
		if (ttyfd > STDERR_FILENO)
		{
			dup2(ttyfd, STDIN_FILENO);
			close(ttyfd);
		}
		return (false);
	}
	return (true);
}

static t_bool	_setup_heredoc(t_excmd **cmds, t_execvars *vars)
{
	t_excmd			*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->in_redirects.size
			&& _read_heredocs(&cmd->in_redirects) == EXIT_FAILURE)
		{
			clear_every_tmpfile(cmds);
			puterr(ft_sprintf(": heredoc error.\n"), false);
			vars->status = 1;
			return (true);
		}
		cmd = cmd->next;
	}
	return (false);
}

t_execvars	*exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_execvars		*vars;

	vars = create_execvars(minishell, cmds);
	if (vars == NULL)
	{
		puterr(ft_sprintf(": error:  Memory allocation error\n"), false);
		return (NULL);
	}
	if (vars->nb_cmd == 0 || load_env_strlst(vars) == false)
		return (vars);
	init_sighandler_heredoc();
	if (_setup_heredoc(cmds, vars))
		return (vars);
	init_sighandler();
	if (_handle_signal() == true)
	{
		if (vars->nb_cmd == 1 && (*vars->cmds)->proto != NULL)
			exec_single_builtin(*(vars->cmds));
		else
			exec_multiple_commands(vars);
	}
	free_cmds(vars->cmds);
	ft_free_strtab(minishell->env.envlst);
	return (vars);
}

static t_exit	_read_heredocs_next(t_redir_manager *redirects_manager,
					size_t nb_heredoc)
{
	t_redir	*elt;
	t_exit	heredoc_status;

	elt = *redirects_manager->redirects;
	while (elt)
	{
		if (elt->is_heredoc)
		{
			heredoc_status = heredoc(
					elt->heredoc_del,
					&elt->filepath,
					elt->heredoc_id != nb_heredoc
					&& elt->next == NULL);
			if (heredoc_status == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		elt = elt->next;
	}
	return (EXIT_SUCCESS);
}

static t_exit	_read_heredocs(t_redir_manager *redirects_manager)
{
	t_redir	*elt;
	size_t	nb_heredoc;

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
	return (_read_heredocs_next(redirects_manager, nb_heredoc));
}
