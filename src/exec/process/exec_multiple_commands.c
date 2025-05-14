/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:24:04 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 17:04:40 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_setup_cmd(t_excmd *cmd)
{
	if (_check_input_redir(cmd) == EXIT_FAILURE)
		return (cmd->vars->status);
	if (_check_output_redir(cmd) == EXIT_FAILURE)
		return (cmd->vars->status);
	if (_create_input_dup2_redir(cmd) == EXIT_FAILURE)
	{
		close_pipe(cmd, 3);
		return (cmd->vars->status);
	}
	if (_create_output_dup2_redir(cmd) == EXIT_FAILURE)
	{
		close_pipe(cmd, 3);
		return (cmd->vars->status);
	}
	close_pipe(cmd, 3);
	return (EXIT_SUCCESS);
}

int	_check_input_redir(t_excmd *cmd)
{
	if (cmd->in_redirects.size > 0
		&& get_last_redirect(&cmd->in_redirects) == NULL)
	{
		cmd->vars->status = EXIT_FAILURE;
		return (cmd->vars->status);
	}
	else if (cmd->in_redirects.size == 0 && cmd->id > 1)
	{
		if (cmd->prev)
			cmd->in_redirects.final_fd.fd = cmd->prev->pipe[0];
		cmd->in_redirects.final_fd.type = STREAM_PIPE;
	}
	return (cmd->vars->status);
}

int	_check_output_redir(t_excmd *cmd)
{
	if (cmd->out_redirects.size > 0
		&& get_last_redirect(&cmd->out_redirects) == NULL)
	{
		if (cmd->in_redirects.size > 0
			&& cmd->in_redirects.final_fd.type == STREAM_REDIR)
			close(cmd->in_redirects.final_fd.fd);
		cmd->vars->status = EXIT_FAILURE;
		return (cmd->vars->status);
	}
	else if (cmd->out_redirects.size == 0 && cmd->id < cmd->vars->nb_cmd)
	{
		cmd->out_redirects.final_fd.fd = cmd->pipe[1];
		cmd->out_redirects.final_fd.type = STREAM_PIPE;
	}
	return (cmd->vars->status);
}

int	_create_input_dup2_redir(t_excmd *cmd)
{
	if (cmd->in_redirects.final_fd.type != STREAM_STD)
	{
		if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
		{
			puterr(ft_sprintf(": %s(%d) dup2 input error", cmd->name, cmd->id),
				true);
			if (cmd->in_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->in_redirects.final_fd.fd);
			if (cmd->out_redirects.size > 0
				&& cmd->out_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			if (cmd->in_redirects.final_fd.type == STREAM_REDIR
				&& cmd->in_redirects.last->is_heredoc == true)
				unlink(cmd->in_redirects.last->filepath);
			return (cmd->vars->status);
		}
		if (cmd->in_redirects.final_fd.type == STREAM_REDIR
			&& cmd->in_redirects.final_fd.fd > STDERR_FILENO)
			close(cmd->in_redirects.final_fd.fd);
	}
	return (cmd->vars->status);
}

int	_create_output_dup2_redir(t_excmd *cmd)
{
	if (cmd->out_redirects.final_fd.type != STREAM_STD)
	{
		if (dup2(cmd->out_redirects.final_fd.fd, STDOUT_FILENO) == -1)
		{
			puterr(ft_sprintf(": %s(%d) dup2 output error", cmd->name, cmd->id),
				true);
			if (cmd->out_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return (cmd->vars->status);
		}
		if (cmd->out_redirects.final_fd.type == STREAM_REDIR)
			close(cmd->out_redirects.final_fd.fd);
	}
	return (cmd->vars->status);
}
