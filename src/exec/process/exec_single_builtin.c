/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:24:08 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 15:16:41 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_setup_redirs(t_excmd *cmd)
{
	if (cmd->proto == NULL)
	{
		puterr(ft_sprintf(": %s: Command not found\n", cmd->name), false);
		cmd->vars->status = 127;
		return (true);
	}
	if (cmd->in_redirects.size > 0
		&& get_last_redirect(&cmd->in_redirects) == NULL)
	{
		cmd->vars->status = EXIT_FAILURE;
		return (true);
	}
	if (cmd->out_redirects.size > 0
		&& get_last_redirect(&cmd->out_redirects) == NULL)
	{
		if (cmd->in_redirects.final_fd.fd > STDERR_FILENO)
			close(cmd->in_redirects.final_fd.fd);
		cmd->vars->status = EXIT_FAILURE;
		return (true);
	}
	return (false);
}

static t_bool	_setup_input_fd(t_excmd *cmd, int *stdin_dup)
{
	if (cmd->in_redirects.final_fd.type == STREAM_REDIR
		&& cmd->in_redirects.last->is_heredoc == false)
	{
		*stdin_dup = dup(STDIN_FILENO);
		if (*stdin_dup == -1)
		{
			puterr(ft_sprintf(": dup error"), true);
			close(cmd->in_redirects.final_fd.fd);
			close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return (true);
		}
		if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
		{
			puterr(ft_sprintf(": dup2 error"), true);
			close(cmd->in_redirects.final_fd.fd);
			close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return (true);
		}
		close(cmd->in_redirects.final_fd.fd);
	}
	return (false);
}

static t_bool	_setup_output_fd(t_excmd *cmd, int stdin_dup, int *stdout_dup)
{
	if (cmd->out_redirects.final_fd.type == STREAM_REDIR)
	{
		*stdout_dup = dup(STDOUT_FILENO);
		if (*stdout_dup == -1)
		{
			puterr(ft_sprintf(": dup error"), true);
			close(cmd->out_redirects.final_fd.fd);
			dup2(stdin_dup, STDIN_FILENO);
			close(stdin_dup);
			cmd->vars->status = EXIT_FAILURE;
			return (true);
		}
		if (dup2(cmd->out_redirects.final_fd.fd, STDOUT_FILENO) == -1)
		{
			puterr(ft_sprintf(": dup2 error"), true);
			close(cmd->out_redirects.final_fd.fd);
			dup2(stdin_dup, STDIN_FILENO);
			close(stdin_dup);
			cmd->vars->status = EXIT_FAILURE;
			return (true);
		}
		close(cmd->out_redirects.final_fd.fd);
	}
	return (false);
}

void	exec_single_builtin(t_excmd *cmd)
{
	int	stdin_dup;
	int	stdout_dup;

	stdin_dup = -1;
	stdout_dup = -1;
	if (_setup_redirs(cmd))
		return ;
	if (_setup_input_fd(cmd, &stdin_dup))
		return ;
	if (_setup_output_fd(cmd, stdin_dup, &stdout_dup))
		return ;
	cmd->vars->status = cmd->proto(cmd);
	if (stdin_dup != -1)
	{
		dup2(stdin_dup, STDIN_FILENO);
		close(stdin_dup);
	}
	if (stdout_dup != -1)
	{
		dup2(stdout_dup, STDOUT_FILENO);
		close(stdout_dup);
	}
}
