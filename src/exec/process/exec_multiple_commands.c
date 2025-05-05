#include "minishell.h"

static int	_setup_cmd(t_excmd *cmd);
static int	_check_input_redir(t_excmd *cmd);
static int	_check_output_redir(t_excmd *cmd);
static int	_create_input_dup2_redir(t_excmd *cmd);
static int	_create_output_dup2_redir(t_excmd *cmd);

void	exec_multiple_commands(t_execvars *vars)
{
	t_excmd	*cmd;
	pid_t	fork_id;
	pid_t	last_fork;
	int		status;

	cmd = *vars->cmds;
	while (cmd)
	{
		// ouverture de la pipe si pas derniere cmd
		if (cmd->id < cmd->vars->nb_cmd)
		{
			if (pipe(cmd->pipe) == -1)
			{
				
			}
			cmd->pipe_open[0] = true;
			cmd->pipe_open[1] = true;
		}
		fork_id = fork();
		if (fork_id == 0)
		{
			if (cmd->id < cmd->vars->nb_cmd) // Si un pipe a été créé pour la commande actuelle
			{
				close(cmd->pipe[0]); // Ferme l'extrémité de lecture du pipe (non utilisée par l'enfant)
			}
			if (cmd->prev) // Si la commande précédente a un pipe
			{
				close(cmd->prev->pipe[1]); // Ferme l'extrémité d'écriture du pipe précédent
			}
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
		if (cmd->id < cmd->vars->nb_cmd) // Si un pipe a été créé pour la commande actuelle
		{
			close(cmd->pipe[0]); // Ferme l'extrémité de lecture du pipe
			close(cmd->pipe[1]); // Ferme l'extrémité d'écriture du pipe
		}
		if (cmd->prev) // Si la commande précédente a un pipe
		{
			close(cmd->prev->pipe[0]); // Ferme l'extrémité de lecture du pipe précédent
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
	if (_check_input_redir(cmd) == EXIT_FAILURE)
		return (cmd->vars->status);
	if (_check_output_redir(cmd) == EXIT_FAILURE)
		return (cmd->vars->status);

	if (cmd->in_redirects.final_fd.type == STREAM_STD)
		printf("[%s %zu] input fd: %d\ttype: STANDARD\n", cmd->name, cmd->id, cmd->in_redirects.final_fd.fd);
	if (cmd->in_redirects.final_fd.type == STREAM_REDIR)
		printf("[%s %zu] input fd: %d\ttype: REDIRECT\n", cmd->name, cmd->id, cmd->in_redirects.final_fd.fd);
	if (cmd->in_redirects.final_fd.type == STREAM_PIPE)
		printf("[%s %zu] input fd: %d\ttype: PIPE\n", cmd->name, cmd->id, cmd->in_redirects.final_fd.fd);

	if (cmd->out_redirects.final_fd.type == STREAM_STD)
		printf("[%s %zu] output fd: %d\ttype: STANDARD\n", cmd->name, cmd->id, cmd->out_redirects.final_fd.fd);
	if (cmd->out_redirects.final_fd.type == STREAM_REDIR)
		printf("[%s %zu] output fd: %d\ttype: REDIRECT\n", cmd->name, cmd->id, cmd->out_redirects.final_fd.fd);
	if (cmd->out_redirects.final_fd.type == STREAM_PIPE)
		printf("[%s %zu] output fd: %d\ttype: PIPE\n", cmd->name, cmd->id, cmd->out_redirects.final_fd.fd);

	// creation des dups
	if (_create_input_dup2_redir(cmd) == EXIT_FAILURE)
	{
		return (cmd->vars->status);
	}
	if (_create_output_dup2_redir(cmd) == EXIT_FAILURE)
	{
		return (cmd->vars->status);
	}
	return (EXIT_SUCCESS);
}

static int	_check_input_redir(t_excmd *cmd)
{
	if (cmd->in_redirects.size > 0 && get_last_redirect(&cmd->in_redirects) == NULL)
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

static int	_check_output_redir(t_excmd *cmd)
{
	if (cmd->out_redirects.size > 0 && get_last_redirect(&cmd->out_redirects) == NULL)
	{
		if (cmd->in_redirects.size > 0 && cmd->in_redirects.final_fd.type == STREAM_REDIR)
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

static int	_create_input_dup2_redir(t_excmd *cmd)
{
	if (cmd->in_redirects.final_fd.type != STREAM_STD && cmd->in_redirects.last->is_heredoc == false)
	{
		if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
		{
			puterr(ft_sprintf(": dup2 error"), true);
			if (cmd->in_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->in_redirects.final_fd.fd);
			if (cmd->out_redirects.size > 0 && cmd->out_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			return (cmd->vars->status);
		}
		if (cmd->in_redirects.final_fd.type == STREAM_REDIR)
			close(cmd->in_redirects.final_fd.fd);
	}
	return (cmd->vars->status);
}

static int	_create_output_dup2_redir(t_excmd *cmd)
{
	if (cmd->out_redirects.final_fd.type != STREAM_STD)
	{
		if (dup2(cmd->out_redirects.final_fd.fd, STDOUT_FILENO) == -1)
		{
			puterr(ft_sprintf(": dup2 error"), true);
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
