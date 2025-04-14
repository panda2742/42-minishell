#include "minishell.h"

static char	*_get_full_path(char *path, char *cmd_name);

t_exit	exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_cmdproto		*proto;
	(void)proto;
	t_excmd			*cmd;
	t_execparams	params;

	int				forkid;

	minishell->last_status = EXIT_SUCCESS;
	proto = NULL;
	params.nb_cmd = 0;
	params.nb_launched = 0;
	params.cmds = cmds;
	minishell->env.envlst = env_to_strlst(&minishell->env);

	size_t			i;

	(void)minishell;
	// loading params and heredoc
	cmd = *cmds;
	i = 0;
	while (cmd)
	{
		params.nb_cmd++;
		cmd->id = i;
		cmd->proto = load_builtin(cmd->name, &cmd->proto);
		i++;
		cmd = cmd->next;
	}

	// exec
	cmd = *cmds;
	while (cmd)
	{
		cmd->envp = minishell->env.envlst;

		if (cmd->proto != NULL && params.nb_cmd == 1)
			cmd->in_a_child = false;

		// ouverture de la pipe
		if (cmd->id != i)
		{
			cmd->pipe_open = true;
			pipe(cmd->pipe);
		}

		// mettre l'ouverture ici
		if (get_last_redirect(&cmd->in_redirects) == NULL && cmd->in_redirects.size > 0)
		{
			if (cmd->in_redirects.problematic && cmd->in_redirects.problematic->filepath)
				puterr(ft_sprintf(": %s", cmd->in_redirects.problematic->filepath), true);
			else
				puterr(ft_sprintf(": input redirecting"), true);
			close(cmd->pipe[0]);
			close(cmd->pipe[1]);
			cmd = cmd->next;
			continue ;
		}
		if (get_last_redirect(&cmd->out_redirects) == NULL && cmd->out_redirects.size > 0)
		{
			if (cmd->in_redirects.problematic && cmd->in_redirects.problematic->filepath)
				puterr(ft_sprintf(": %s", cmd->in_redirects.problematic->filepath), true);
			else
				puterr(ft_sprintf(": output redirecting"), true);
			close(cmd->pipe[0]);
			close(cmd->pipe[1]);
			cmd = cmd->next;
			continue ;
		}

		print_cmd(cmd);

		params.nb_launched++;
		// creation du process
		if (cmd->in_a_child)
		{
			forkid = fork();
			if (forkid > 0 || forkid < 0)
			{
				close(cmd->pipe[0]);
				close(cmd->pipe[1]);
				if (forkid == -1)
				{
					params.nb_launched--;
					puterr(ft_sprintf(": fork error"), true);
				}
				cmd = cmd->next;
				continue ;
			}
		}

		// creation de la duplication
		dup2(cmd->in_redirects.final_fd, STDIN_FILENO);
		dup2(cmd->out_redirects.final_fd, STDOUT_FILENO);

		close(cmd->pipe[0]);
		close(cmd->pipe[1]);

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

			size_t i = 0;
			// test de l'access et de l'execve
			while (cmd->paths[i])
			{
				char *fullpath = _get_full_path(cmd->paths[i], cmd->name);
				i++;
				if (access(fullpath, F_OK | X_OK) != 0)
					continue ;
				if (execve(fullpath, cmd->argv, cmd->envp) == -1)
					break ;
			}
			if (access(cmd->name, F_OK | X_OK) == 0)
				execve(cmd->name, cmd->argv, cmd->envp);
			free_env(cmd->env);
			ft_free_strtab(cmd->envp);
			free_cmds(cmds);
			puterr(ft_sprintf(": %s", cmd->name), true);
			exit(0);
		}
		else
			(*cmd->proto)(cmd);

		free_env(cmd->env);
		ft_free_strtab(cmd->envp);
		free_cmds(cmds);
		if (cmd->in_a_child)
			exit(0);
		else
			cmd = cmd->next;
	}
	while (params.nb_launched)
	{
		waitpid(-1, NULL, 0);
		params.nb_launched--;
	}
	ft_free_strtab(minishell->env.envlst);
	return (minishell->last_status);
}

static char	*_get_full_path(char *path, char *cmd_name)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp2, cmd_name);
	return (tmp);
}

t_cmdproto	load_builtin(const char *command_name, t_cmdproto *proto)
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
			*proto = command_prototypes[i];
			break ;
		}
	}
	return (*proto);
}
