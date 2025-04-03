#include "minishell.h"

t_exit	exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_cmdproto		*proto;
	t_excmd			*cmd;
	t_execparams	params;

	int				fork_id;

	minishell->last_status = EXIT_SUCCESS;
	proto = NULL;
	params.nb_cmd = 0;
	params.cmds = cmds;

	size_t			i;

	(void)minishell;
	// loading params and heredocs
	cmd = *cmds;
	i = 0;
	while (cmd)
	{
		if (cmd->has_heredoc)
			heredoc(cmd->heredoc_del, cmd->heredoc_content);
		params.nb_cmd++;
		cmd->_id = i;
		load_builtin(cmd->name, &cmd->proto);
		i++;
	}

	// exec
	cmd = *cmds;
	while (cmd)
	{
		cmd->in_a_child = true;
		if (cmd->proto != NULL && params.nb_cmd == 1)
			cmd->in_a_child = false;

		// builtins dans le main process ?
		if (!cmd->in_a_child)
		{
			(*cmd->proto)(cmd);
			cmd = cmd->next;
			break ;
		}

		// ouverture de la pipe
		if (cmd->_id != i)
			pipe(cmd->pipe);

		// ouverture des fichiers d'entree et de sortie
		cmd->in_fd = STDIN_FILENO;
		if (cmd->infile != NULL)
			cmd->in_fd = open(cmd->infile, O_RDONLY);

		cmd->out_fd = STDOUT_FILENO;
		if (cmd->outfile != NULL)
		{
			if (cmd->out_append_mode)
				cmd->out_fd = open(cmd->infile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				cmd->out_fd = open(cmd->infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}

		// creation du process
		fork_id = fork();
		if (fork_id || fork_id < 0)
		{	
			cmd = cmd->next;
			continue ;
		}

		// creation de la duplication
		dup2(cmd->in_fd, STDIN_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);

		// on close la pipe de la commande precedente apres l'avoir lue
		if (cmd->_id != 0)
		{
			close(cmd->prev->pipe[0]);
			close(cmd->prev->pipe[1]);
		}
		break ;
	}
	return (minishell->last_status);
}

t_cmdproto	*load_builtin(const char *command_name, t_cmdproto *proto)
{
	static char			*builtins[7] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"
	};
	static t_cmdproto	command_prototypes[7] = {
		builtins_cd, builtins_echo, builtins_env, builtins_exit,
		builtins_export, builtins_pwd, builtins_unset
	};
	size_t				len;
	int					i;

	i = -1;
	while (++i < 7)
	{
		len = ft_strlen(builtins[i]);
		if (ft_strncmp(command_name, builtins[i], len) == 0)
		{
			proto = &command_prototypes[i];
			break ;
		}
	}
	return (proto);
}
