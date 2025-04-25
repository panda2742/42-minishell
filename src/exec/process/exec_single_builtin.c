#include "minishell.h"

void	exec_single_builtin(t_excmd *cmd)
{
	int	stdin_dup;
	int	stdout_dup;

	if (cmd->proto == NULL)
	{
		puterr(ft_sprintf(": %s: Command not found\n", cmd->name), false);
		cmd->vars->status = 127;
		return ;
	}

	// ouverture du dernier redir
	if (cmd->in_redirects.size > 0 && get_last_redirect(&cmd->in_redirects) == NULL)
	{
		cmd->vars->status = EXIT_FAILURE;
		return ;
	}
	if (cmd->out_redirects.size > 0 && get_last_redirect(&cmd->out_redirects) == NULL)
	{
		close(cmd->in_redirects.final_fd.fd);
		cmd->vars->status = EXIT_FAILURE;
		return ;
	}

	// creation des dups
	stdin_dup = -1;
	stdout_dup = -1;
	if (cmd->in_redirects.final_fd.type == STREAM_REDIR && cmd->in_redirects.last->is_heredoc == false)
	{
		// dup de stdin pour restoration
		stdin_dup = dup(STDIN_FILENO);
		if (stdin_dup == -1)
		{
			puterr(ft_sprintf(": dup error"), true);
			close(cmd->in_redirects.final_fd.fd);
			close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return ;
		}

		if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
		{
			puterr(ft_sprintf(": dup2 error"), true);
			close(cmd->in_redirects.final_fd.fd);
			close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return ;
		}
		close(cmd->in_redirects.final_fd.fd);
	}

	if (cmd->out_redirects.final_fd.type == STREAM_REDIR)
	{
		// dup de stdout pour restoration
		stdout_dup = dup(STDOUT_FILENO);
		if (stdout_dup == -1)
		{
			puterr(ft_sprintf(": dup error"), true);
			close(cmd->out_redirects.final_fd.fd);
			dup2(stdin_dup, STDIN_FILENO);
			close(stdin_dup);
			cmd->vars->status = EXIT_FAILURE;
			return ;
		}

		if (dup2(cmd->out_redirects.final_fd.fd, STDOUT_FILENO) == -1)
		{
			puterr(ft_sprintf(": dup2 error"), true);
			close(cmd->out_redirects.final_fd.fd);
			dup2(stdin_dup, STDIN_FILENO);
			close(stdin_dup);
			cmd->vars->status = EXIT_FAILURE;
			return ;
		}
		close(cmd->out_redirects.final_fd.fd);
	}

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
