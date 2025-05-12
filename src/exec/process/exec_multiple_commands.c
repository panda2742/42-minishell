#include "minishell.h"

static int	_setup_cmd(t_excmd *cmd);
static int	_check_input_redir(t_excmd *cmd);
static int	_check_output_redir(t_excmd *cmd);
static int	_create_input_dup2_redir(t_excmd *cmd);
static int	_create_output_dup2_redir(t_excmd *cmd);
static int	_write_heredoc(char *buffer, char **filepath);

void	exec_multiple_commands(t_execvars *vars)
{
	t_excmd	*cmd;
	pid_t	fork_id;
	pid_t	last_fork;
	int		status;
	pid_t	ended_pid;
	int		wait_status;

	cmd = *vars->cmds;
	while (cmd)
	{
		// ouverture de la pipe si pas derniere cmd
		if (cmd->id < cmd->vars->nb_cmd)
		{
			if (pipe(cmd->pipe) == -1)
			{
				// securiser l'ouverture de la pipe ici
			}
			cmd->pipe_open[0] = true;
			cmd->pipe_open[1] = true;
		}
		fork_id = fork();
		// child
		if (fork_id == 0)
		{
			status = _setup_cmd(cmd);
			close_pipe(cmd, 3);
			if (cmd->prev)
				close_pipe(cmd->prev, 1);
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
		}
		if (fork_id < 0)
		{
			vars->status = EXIT_FORK_FAILED;
			puterr(ft_sprintf(": Pipeline stopped; %d failed", fork_id), true);
			close_pipe(cmd, 3);
			break ;
		}
		close_pipe(cmd, 2);
		if (cmd->prev)
			close_pipe(cmd->prev, 1);
		if (cmd->next == NULL)
			last_fork = fork_id;
		vars->nb_launched++;
		cmd = cmd->next;
	}
	while (vars->nb_launched)
	{
		ended_pid = waitpid(-1, &wait_status, 0);
		if (ended_pid == last_fork)
		{
			if (WIFEXITED(wait_status))
				vars->status = WEXITSTATUS(wait_status);
		}
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
	// creation des dups
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
	if (cmd->in_redirects.final_fd.type != STREAM_STD)
	{
		if (cmd->in_redirects.final_fd.type == STREAM_REDIR && cmd->in_redirects.last->is_heredoc == true)
			cmd->in_redirects.final_fd.fd = _write_heredoc(cmd->in_redirects.last->heredoc_content, &cmd->in_redirects.last->filepath);
		if (dup2(cmd->in_redirects.final_fd.fd, STDIN_FILENO) == -1)
		{
			puterr(ft_sprintf(": %s dup2 input error", cmd->name), true);
			if (cmd->in_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->in_redirects.final_fd.fd);
			if (cmd->out_redirects.size > 0 && cmd->out_redirects.final_fd.type == STREAM_REDIR)
				close(cmd->out_redirects.final_fd.fd);
			cmd->vars->status = EXIT_FAILURE;
			if (cmd->in_redirects.final_fd.type == STREAM_REDIR && cmd->in_redirects.last->is_heredoc == true)
				unlink(cmd->in_redirects.last->filepath);
			return (cmd->vars->status);
		}
		if (cmd->in_redirects.final_fd.type == STREAM_REDIR)
			close(cmd->in_redirects.final_fd.fd);
		if (cmd->in_redirects.final_fd.type == STREAM_REDIR && cmd->in_redirects.last->is_heredoc == true)
			unlink(cmd->in_redirects.last->filepath);
	}
	return (cmd->vars->status);
}

static int	_create_output_dup2_redir(t_excmd *cmd)
{
	if (cmd->out_redirects.final_fd.type != STREAM_STD)
	{
		if (dup2(cmd->out_redirects.final_fd.fd, STDOUT_FILENO) == -1)
		{
			puterr(ft_sprintf(": %s dup2 output error", cmd->name), true);
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

static int	_write_heredoc(char *buffer, char **filepath)
{
	ssize_t	buffer_len;
	char	*random_id;
	int		heredoc_fd;

	random_id = get_random_chars(24);
	*filepath = ft_sprintf("/tmp/minishell_heredoc_%s", random_id);
	heredoc_fd = open(*filepath, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(random_id);
	if (heredoc_fd == -1)
		return (-1);
	buffer_len = (ssize_t)ft_strlen(buffer);
	while ((buffer_len - 4096) > 0)
	{
		write(heredoc_fd, buffer, 4096);
		buffer += 4096;
		buffer_len -= 4096;
	}
	write(heredoc_fd, buffer, buffer_len);
	free(buffer);
	return (heredoc_fd);
}
