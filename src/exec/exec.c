#include "minishell.h"

static char	*_get_full_path(char *path, char *cmd_name);

t_exit	exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_cmdproto		*proto;
	t_excmd			*cmd;
	t_execparams	params;

	int				forkid;

	minishell->last_status = EXIT_SUCCESS;
	proto = NULL;
	params.nb_cmd = 0;
	params.cmds = cmds;

	size_t			i;

	(void)minishell;
	// loading params and heredoc
	cmd = *cmds;
	i = 0;
	while (cmd)
	{
		params.nb_cmd++;
		cmd->id = i;
		load_builtin(cmd->name, &cmd->proto);
		printf("[%s%s%s|%s%zu%s]\n", B_BLUE, cmd->raw, RESET, B_RED, cmd->id, RESET);
		i++;
		cmd = cmd->next;
	}

	// exec
	cmd = *cmds;
	while (cmd)
	{
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
		if (cmd->id != i)
		{
			cmd->pipe_open = true;
			pipe(cmd->pipe);
		}

		// mettre l'ouverture ici
		get_last_redirect(&cmd->in_redirects);
		get_last_redirect(&cmd->out_redirects);

		// creation du process
		forkid = fork();
		if (forkid > 0 || forkid < 0)
		{	
			cmd = cmd->next;
			continue ;
		}

		// creation de la duplication
		dup2(cmd->in_redirects.final_fd, STDIN_FILENO);
		dup2(cmd->out_redirects.final_fd, STDOUT_FILENO);

		// fermeture des file descriptors inutiles
		if (cmd->in_redirects.final_fd > STDIN_FILENO)
			close(cmd->in_redirects.final_fd);
		if (cmd->out_redirects.final_fd > STDOUT_FILENO)
			close(cmd->out_redirects.final_fd);

		// récupération des paths si c'est pas un builtin
		if (cmd->proto == NULL)
		{
			t_env_var	*path_var = get_var(&minishell->env, "PATH");
			if (path_var != NULL)
				cmd->paths = ft_split(path_var->value, ":");
			else
				cmd->paths = empty_tab();
	
			// test de l'access et de l'execve
			while (*cmd->paths)
			{
				char *fullpath = _get_full_path(*cmd->paths, cmd->name);
				if (access(fullpath, X_OK) != 0)
					continue ;
				if (execve(fullpath, cmd->argv, cmd->envp) == -1)
					break ;
				cmd->paths++;
			}
		}
		else
			(*cmd->proto)(cmd);

		free_env(cmd->env);
		ft_free_strtab(cmd->envp);
		free_cmds(cmds);
		exit(0);
	}
	waitpid(-1, NULL, 0);
	return (minishell->last_status);
}

static char	*_get_full_path(char *path, char *cmd_name)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("/", path);
	tmp2 = ft_strjoin(tmp, "/");
	tmp = ft_strjoin(tmp2, cmd_name);
	return (tmp);
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
	*proto = NULL;
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
