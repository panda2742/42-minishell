#include "minishell.h"

static int	_setup_cmd(t_excmd *cmd);

void	exec_multiple_commands(t_execvars *vars)
{
	t_excmd	*cmd;
	pid_t	fork_id;
	pid_t	last_fork;
	int		status;

	cmd = *vars->cmds;
	while (cmd)
	{
		fork_id = fork();
		if (fork_id == 0)
		{
			status = _setup_cmd(cmd);
			if (status != EXIT_SUCCESS)
			{
				ft_free_strtab(cmd->vars->minishell->env.envlst);
				free_env(&cmd->vars->minishell->env);
				free_cmds(vars->cmds);
				free(vars);
				exit(status);
			}
			if (cmd->proto == NULL)
			{
				execute_from_path(cmd);
				ft_free_strtab(cmd->vars->minishell->env.envlst);
				free_env(&cmd->vars->minishell->env);
				status = vars->status;
				free_cmds(vars->cmds);
				free(vars);
				exit(status);
			}
			else
			{
				status = cmd->proto(cmd);
				ft_free_strtab(cmd->vars->minishell->env.envlst);
				free_env(&cmd->vars->minishell->env);
				free_cmds(vars->cmds);
				free(vars);
				exit(status);
			}
			// au cas ou...
			exit(status);
		}
		if (cmd->next == NULL)
			last_fork = fork_id;
		vars->nb_launched++;
		if (fork_id < 0)
		{
			vars->status = EXIT_FORK_FAILED;
			puterr(ft_sprintf(": Pipeline stopped; %d failed", fork_id), true);
			vars->nb_launched--;
			break ;
		}
		cmd = cmd->next;
	}
	waitpid(last_fork, &vars->minishell->last_status, 0);
	while (vars->nb_launched - 1)
	{
		waitpid(-1, NULL, 0);
		vars->nb_launched--;
	}
}

static int	_setup_cmd(t_excmd *cmd)
{
	// ouverture du dernier redir
	if (cmd->in_redirects.size > 0 && get_last_redirect(&cmd->in_redirects) == NULL)
	{
		cmd->vars->status = EXIT_FAILURE;
		return (cmd->vars->status);
	}
	if (cmd->out_redirects.size > 0 && get_last_redirect(&cmd->out_redirects) == NULL)
	{
		close(cmd->in_redirects.final_fd.fd);
		cmd->vars->status = EXIT_FAILURE;
		return (cmd->vars->status);
	}

	// creation des dups
	if (cmd->in_redirects.final_fd.type == STREAM_REDIR && cmd->in_redirects.last->is_heredoc == false)
	{
		if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
		{
			puterr(ft_sprintf(": dup2 error"), true);
			close(cmd->in_redirects.final_fd.fd);
			close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return (cmd->vars->status);
		}
		close(cmd->in_redirects.final_fd.fd);
	}

	if (cmd->out_redirects.final_fd.type == STREAM_REDIR)
	{
		if (dup2(cmd->out_redirects.final_fd.fd, STDOUT_FILENO) == -1)
		{
			puterr(ft_sprintf(": dup2 error"), true);
			close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return (cmd->vars->status);
		}
		close(cmd->out_redirects.final_fd.fd);
	}
	return (EXIT_SUCCESS);
}
